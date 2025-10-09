using UnrealBuildTool;

public class OmniWaveCore : ModuleRules
{
	public OmniWaveCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
		PrivateDependencyModuleNames.AddRange(new string[] { "OmniWaveAssets" });
	}
}