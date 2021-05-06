// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "HUDWidget.h"
#include "FPS/APlayerTeam.h"

#include "FPSCharacter.generated.h"



USTRUCT()
struct FPlayerTeamID : public FGenericTeamId
{
	//GENERATED_BODY()
	GENERATED_USTRUCT_BODY()
		FPlayerTeamID() : FGenericTeamId(PlayerTeam) {}
};

UCLASS()
class FPS_API AFPSCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void MoveForward(float value);

	UFUNCTION()
		void MoveRight(float value);

	UFUNCTION()
		void Fire();

	UFUNCTION(BlueprintCallable)
		void ChangeFireType();

	UFUNCTION(BlueprintImplementableEvent)
		FVector GetMuzzleLocation();

public:
	virtual FGenericTeamId GetGenericTeamId() const override;
	bool bSinFire = true;
	
protected:
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* GunSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UHUDWidget> HUDClass;
	
	UPROPERTY(BlueprintReadWrite)
		UHUDWidget* HUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 BulletsCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxBulletsCount;
	

private:
	FPlayerTeamID TeamID;
};