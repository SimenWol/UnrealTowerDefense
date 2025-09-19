using UnrealBuildTool;

public class OmniCameraCore : ModuleRules
{
    public OmniCameraCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}