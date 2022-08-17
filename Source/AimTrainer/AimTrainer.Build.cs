// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AimTrainer : ModuleRules
{
    public AimTrainer(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] { 
            "AimTrainer/Public/Components",
            "AimTrainer/Public/Enemy",
            "AimTrainer/Public/Menu",
            "AimTrainer/Public/Player",
            "AimTrainer/Public/UI",
            "AimTrainer/Public/Weapon",
            "AimTrainer/Settings"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
