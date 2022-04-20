// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Testing : ModuleRules
{
	public Testing(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//umg - user interface system
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
