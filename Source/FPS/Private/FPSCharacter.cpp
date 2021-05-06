// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS/Public/FPSCharacter.h"

#include "Projectile.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(CameraComponent != nullptr);
	CameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	CameraComponent->bUsePawnControlRotation = true;
	
	GetMesh()->SetupAttachment(CameraComponent);
	GetMesh()->bCastDynamicShadow = false;

	GunSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunSkeletalMeshComponent"));
	GunSkeletalMeshComponent->bCastDynamicShadow = false;
	GunSkeletalMeshComponent->CastShadow = false;
	GunSkeletalMeshComponent->SetupAttachment(CameraComponent);

	MaxBulletsCount = 6;
	BulletsCount = MaxBulletsCount;
	
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	GunSkeletalMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponPoint"));

	HUD = CreateWidget<UHUDWidget>(GetWorld(), HUDClass);
	HUD->AddToViewport();
	HUD->SetBullet(BulletsCount);
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed,this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(GetCapsuleComponent()->GetForwardVector(), value);
}

void AFPSCharacter::MoveRight(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::Fire()
{
	if(BulletsCount > 0)
	{
		check(ProjectileClass != nullptr)

			FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = GetMuzzleLocation();

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = GetInstigator();

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, CameraRotation, SpawnParameters);
		if(Projectile)
		{
			Projectile->FireInDirection(CameraRotation.Vector());
			BulletsCount--;
			HUD->SetBullet(BulletsCount);
		}
	}
	
}

void AFPSCharacter::ChangeFireType()
{
	if (bSinFire)
		bSinFire = false;
	else
		bSinFire = true;
}

FGenericTeamId AFPSCharacter::GetGenericTeamId() const
{
	return TeamID.GetId();
}
