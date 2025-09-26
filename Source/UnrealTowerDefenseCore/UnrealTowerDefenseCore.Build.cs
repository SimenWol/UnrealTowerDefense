using UnrealBuildTool;

public class UnrealTowerDefenseCore : ModuleRules
{
    public UnrealTowerDefenseCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PrivateDependencyModuleNames.AddRange(new string[] { "OmniCameraCore" });
    }
}