// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrossHairHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ACrossHairHUD : public AHUD
{
	GENERATED_BODY()


protected:
	virtual void DrawHUD() override;

private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* CrosshairTexture;
};
