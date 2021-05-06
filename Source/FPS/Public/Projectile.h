// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define _USE_MATH_DEFINES
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <math.h>
#include <FPSCharacter.h>
#include "Projectile.generated.h"

UCLASS()
class FPS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& StartDirection);
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
		UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
		FVector Direction;


	UPROPERTY(VisibleAnywhere, Category = Projectile)
		float LifeSpan = 15.0f;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
		float X = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
		bool bSinFireForBullet;
};

