// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstUserWidget.h"

void UMyFirstUserWidget::NativeConstruct()
{
	Button_21->OnReleased.AddUniqueDynamic(this, &UMyFirstUserWidget::OnReleaseHandler);
}

void UMyFirstUserWidget::OnReleaseHandler()
{
	UE_LOG(LogTemp,Log,TEXT("C++ OnReleaseHendler"))
}
