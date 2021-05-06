// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Projectile.h"
#include "Perception/AIPerceptionComponent.h"
#include "GenericTeamAgentInterface.h"
#include "NPCAIController.h"
#include "GameFramework/Character.h"
#include "AI_Character.generated.h"

class UAIPerceptionComponent;
struct FAIStimulus;
UCLASS()
class FPS_API AAI_Character : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void OnReload();

	UFUNCTION(BlueprintCallable)
		void OnReloadCycle();

	UFUNCTION(BlueprintImplementableEvent)
		FVector GetMuzzleLocation();

	UFUNCTION(BlueprintCallable)
		bool OnFire();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnActorPerception(AActor* Actor, FAIStimulus Stimulus);

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UFUNCTION(BlueprintCallable)
		void Walk();
	
	UFUNCTION(BlueprintCallable)
		void Run();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		AActor* PerceivedActor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float WeaponEffectiveRange;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float RunSpeed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float WalkSpeed;

	UPROPERTY(BlueprintReadOnly)
		bool bIsRunning = true;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool bHasLineOfSight = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TargetLastTime;

	UPROPERTY(BlueprintReadWrite)
		bool bIsReloading = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxAmmo;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int32 AmmoInClip;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AProjectile> ProjectileClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ANPCAIController* AIController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsAlive = true;

	float TargetLostElapsed = 0.f;
	float LastLocationElapsed = 0.f;
	float LastLocationUpdateTime = 0.5f;
};
