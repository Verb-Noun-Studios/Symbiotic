// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RLFPS : ModuleRules
{
	public RLFPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Niagara" , "Json", "JsonUtilities", "HTTP", "NavigationSystem" });
	}
}
