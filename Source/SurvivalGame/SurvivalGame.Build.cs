// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SurvivalGame : ModuleRules
{
	public SurvivalGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SurvivalGame",
			"SurvivalGame/Variant_Platforming",
			"SurvivalGame/Variant_Platforming/Animation",
			"SurvivalGame/Variant_Combat",
			"SurvivalGame/Variant_Combat/AI",
			"SurvivalGame/Variant_Combat/Animation",
			"SurvivalGame/Variant_Combat/Gameplay",
			"SurvivalGame/Variant_Combat/Interfaces",
			"SurvivalGame/Variant_Combat/UI",
			"SurvivalGame/Variant_SideScrolling",
			"SurvivalGame/Variant_SideScrolling/AI",
			"SurvivalGame/Variant_SideScrolling/Gameplay",
			"SurvivalGame/Variant_SideScrolling/Interfaces",
			"SurvivalGame/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
