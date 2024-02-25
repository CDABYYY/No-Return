// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Demo0 : ModuleRules
{
	public Demo0(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
