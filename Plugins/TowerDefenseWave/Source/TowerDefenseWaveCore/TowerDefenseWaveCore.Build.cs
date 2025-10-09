using UnrealBuildTool;

public class TowerDefenseWaveCore : ModuleRules
{
    public TowerDefenseWaveCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PrivateDependencyModuleNames.AddRange(new string[] { "OmniWaveCore", "OmniWaveAssets" });
    }
}