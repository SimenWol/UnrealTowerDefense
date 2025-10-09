using UnrealBuildTool;

public class OmniWaveAssets : ModuleRules
{
    public OmniWaveAssets(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}