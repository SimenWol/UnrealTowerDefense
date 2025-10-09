using UnrealBuildTool;

public class TowerDefenseAICore : ModuleRules
{
    public TowerDefenseAICore(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PrivateDependencyModuleNames.AddRange(new string[] { "OmniWaveCore", "OmniWaveAssets" });
    }
}