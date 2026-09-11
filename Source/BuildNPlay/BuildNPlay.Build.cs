// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BuildNPlay : ModuleRules
{
	public BuildNPlay(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"BuildNPlay",
			"BuildNPlay/Variant_Platforming",
			"BuildNPlay/Variant_Platforming/Animation",
			"BuildNPlay/Variant_Combat",
			"BuildNPlay/Variant_Combat/AI",
			"BuildNPlay/Variant_Combat/Animation",
			"BuildNPlay/Variant_Combat/Gameplay",
			"BuildNPlay/Variant_Combat/Interfaces",
			"BuildNPlay/Variant_Combat/UI",
			"BuildNPlay/Variant_SideScrolling",
			"BuildNPlay/Variant_SideScrolling/AI",
			"BuildNPlay/Variant_SideScrolling/Gameplay",
			"BuildNPlay/Variant_SideScrolling/Interfaces",
			"BuildNPlay/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
