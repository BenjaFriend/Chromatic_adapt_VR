// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EJ_EnviornmentEditorTarget : TargetRules
{
	public EJ_EnviornmentEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("EJ_Enviornment");
	}
}
