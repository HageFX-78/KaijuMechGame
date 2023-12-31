// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KaijuGameTest : ModuleRules
{
	public KaijuGameTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
			"AIModule", "NavigationSystem",
			"GameplayTasks", "HeadMountedDisplay", "EnhancedInput" });
	}
}
