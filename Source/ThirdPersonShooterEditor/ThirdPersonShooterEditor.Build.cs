// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ThirdPersonShooterEditor : ModuleRules
{
	public ThirdPersonShooterEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[]{"ThirdPersonShooterEditor"});
	
		PublicDependencyModuleNames.AddRange(new string[]
		                                     {
			                                     "Core", 
			                                     "CoreUObject", 
			                                     "Engine", 
			                                     "EditorFramework", 
			                                     "UnrealEd", 
			                                     "GameplayTagsEditor", 
			                                     "InputCore",
			                                     "Slate",
			                                     "SlateCore",
			                                     "ThirdPersonShooter"
		                                     });

		PrivateDependencyModuleNames.AddRange(new string[] {"InputCore",
		                                                    "Slate",
		                                                    "SlateCore",
		                                                    "ToolMenus",
		                                                    "EditorStyle",
		                                                    "DataValidation",
		                                                    "MessageLog",
		                                                    "Projects",
		                                                    "DeveloperToolSettings",
		                                                    "CollectionManager" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
