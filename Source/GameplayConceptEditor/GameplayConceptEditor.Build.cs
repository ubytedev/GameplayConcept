// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameplayConceptEditor : ModuleRules
{
	public GameplayConceptEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"GameplayTags",
				"GameplayConceptRuntime",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
			}
			);
	}
}
