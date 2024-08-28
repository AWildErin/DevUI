// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DevUI : ModuleRules
{
	public DevUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange( new string[] { } );
		PrivateIncludePaths.AddRange( new string[] { } );
		DynamicallyLoadedModuleNames.AddRange( new string[] { } );

		PublicDependencyModuleNames.AddRange( new string[] { "Core" } );

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"DeveloperSettings",
				"Engine",
                "ImGui",
				"Projects"
			}
		);
	}
}
