// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EJ_EnviornmentGameMode.h"
#include "EJ_EnviornmentHUD.h"
#include "EJ_EnviornmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEJ_EnviornmentGameMode::AEJ_EnviornmentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AEJ_EnviornmentHUD::StaticClass();
}
