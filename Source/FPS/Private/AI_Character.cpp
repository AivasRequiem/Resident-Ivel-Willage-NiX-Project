// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"


#include "BehaviorTree/BlackboardComponent.h"
#include "FPS/APlayerTeam.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAI_Character::AAI_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionComponent = CreateOptionalDefaultSubobject<UAIPerceptionComponent>("AI_Perception");
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Character::OnActorPerception);
	
	RunSpeed = GetCharacterMovement()->MaxWalkSpeed;
	WalkSpeed = RunSpeed / 4;
}

void AAI_Character::OnReload()
{
	if(bIsAlive)
		if(AmmoInClip < MaxAmmo)
		{
			bIsReloading = true;
			AIController->GetBlackboardComponent()->SetValueAsBool(AIController->GetIsReloadingKey(), bIsReloading);
		}
}

void AAI_Character::OnReloadCycle()
{
	if (bIsAlive)
		if (AmmoInClip < MaxAmmo && ++AmmoInClip == MaxAmmo)
		{
			bIsReloading = false;
			AIController->GetBlackboardComponent()->SetValueAsBool(AIController->GetIsReloadingKey(), bIsReloading);
		}
}

bool AAI_Character::OnFire()
{
	if (bIsAlive)
		if(AmmoInClip != 0 && ProjectileClass != NULL)
		{
			bIsReloading = false;
			AIController->GetBlackboardComponent()->SetValueAsBool(AIController->GetIsReloadingKey(), bIsReloading);
			UWorld* const World = GetWorld();
			if(World != NULL)
			{
				const FRotator SpawnRotation = GetControlRotation();
				const FVector SpawnLocation = GetMuzzleLocation();

				FActorSpawnParameters ActorSpawnParameters;

				ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParameters);

				--AmmoInClip;

				return true;
			}
		}
	return false;
}


void AAI_Character::OnActorPerception(AActor* Actor, FAIStimulus Stimulus)
{
	if (bIsAlive)
	{
		bHasLineOfSight = Stimulus.WasSuccessfullySensed();

		AIController->GetBlackboardComponent()->SetValueAsBool(AIController->GetHasLineOfSightKey(), bHasLineOfSight);

		if (Stimulus.WasSuccessfullySensed())
		{
			PerceivedActor = Actor;
			TargetLostElapsed = 0.f;
			AIController->GetBlackboardComponent()->SetValueAsObject(AIController->GetDetectedEnemyKey(), PerceivedActor);
			AIController->GetBlackboardComponent()->SetValueAsVector(AIController->GetLastKnownLocationKey(), PerceivedActor->GetActorLocation());
		}
	}
}

ETeamAttitude::Type AAI_Character::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	return OtherTeamAgent && OtherTeamAgent->GetGenericTeamId().GetId() == PlayerTeam ?
		ETeamAttitude::Hostile : ETeamAttitude::Neutral;
}

// Called every frame
void AAI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsAlive)
	{
		if (bHasLineOfSight && (LastLocationElapsed += DeltaTime) > LastLocationUpdateTime)
		{
			LastLocationElapsed = 0.f;
			AIController->GetBlackboardComponent()->SetValueAsVector(AIController->GetLastKnownLocationKey(), PerceivedActor->GetActorLocation());
		}

		if (!bHasLineOfSight && PerceivedActor && (TargetLostElapsed += DeltaTime) > TargetLastTime)
		{
			PerceivedActor = nullptr;
			TargetLostElapsed = 0.f;
			AIController->GetBlackboardComponent()->SetValueAsObject(AIController->GetDetectedEnemyKey(), PerceivedActor);
		}
	}
}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAI_Character::Walk()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AAI_Character::Run()
{
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}