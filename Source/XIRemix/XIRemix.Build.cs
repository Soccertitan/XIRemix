// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XIRemix : ModuleRules
{
	public XIRemix(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput", 
			"UINavigation",
			"Paper2D"
			});

		PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
			"SlateCore",
			"UMG",
			"GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
        });
	}
}
