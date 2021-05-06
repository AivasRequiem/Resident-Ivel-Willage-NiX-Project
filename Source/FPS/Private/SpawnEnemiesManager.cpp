// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEnemiesManager.h"

#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnEnemiesManager::ASpawnEnemiesManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpawnEnemiesManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundTargetPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), FoundTargetPoints);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for ( AActor * FoundTargetPoint : FoundTargetPoints)
	{
		GetWorld()->SpawnActor<AEnemy>(BaseEnemyBP, FoundTargetPoint->GetActorTransform(), SpawnParameters);
	}
}