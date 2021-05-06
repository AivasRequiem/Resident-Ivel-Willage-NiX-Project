// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	const float GetPatrolRadius() const { return PatrolRadius; }
	const FName& GetPatrolTargetKey() const { return PatrolTargetKey; }
	const FName& GetHasLineOfSightKey() const { return HasLineOfSightKey; }
	const FName& GetDetectedEnemyKey() const { return DetectedEnemyKey; }
	const FName& GetLastKnownLocationKey() const { return LastKnownLocationKey; }
	const FName& GetIsReloadingKey() const { return IsReloadingKey; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float PatrolRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName PatrolTargetKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName HasLineOfSightKey;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName DetectedEnemyKey;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName LastKnownLocationKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName IsReloadingKey;
};
