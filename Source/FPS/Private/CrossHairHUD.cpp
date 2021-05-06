// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "CanvasItem.h"
#include "TextureResource.h"

void ACrossHairHUD::DrawHUD()
{
	Super::DrawHUD();
	if(CrosshairTexture)
	{
		FVector2D Center = FVector2D(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		FVector2D CrosshairDrawPosition = Center - FVector2D(CrosshairTexture->GetSurfaceWidth() * 0.5f, CrosshairTexture->GetSurfaceHeight() * 0.5f);

		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}
