// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TacticalOps : ModuleRules
{
	public TacticalOps(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemUtils" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
