// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MyFirstUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UMyFirstUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION() void OnReleaseHandler();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UButton* Button_21;
};
