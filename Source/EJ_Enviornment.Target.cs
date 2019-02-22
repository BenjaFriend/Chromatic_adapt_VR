// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EJ_EnviornmentTarget : TargetRules
{
	public EJ_EnviornmentTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("EJ_Enviornment");
	}
}
