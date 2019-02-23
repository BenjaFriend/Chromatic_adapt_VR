// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EJ_EnviornmentHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AEJ_EnviornmentHUD::AEJ_EnviornmentHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void AEJ_EnviornmentHUD::DrawHUD()
{
	Super::DrawHUD();
}
