// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EJ_EnviornmentHUD.generated.h"

UCLASS()
class AEJ_EnviornmentHUD : public AHUD
{
	GENERATED_BODY()

public:
	AEJ_EnviornmentHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:

};

