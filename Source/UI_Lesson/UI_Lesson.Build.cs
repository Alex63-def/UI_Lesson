// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UI_Lesson : ModuleRules
{
	public UI_Lesson(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {});
	}
}
