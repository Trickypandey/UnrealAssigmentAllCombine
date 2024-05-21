// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UeCombined : ModuleRules
{
	public UeCombined(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "Assigment1_2" });


        PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[] {
   "D:\\UnrealAssignments\\UnrealAssigmentAllCombine\\Plugins\\Assigment1_2\\Source\\Assigment1_2\\Public" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
