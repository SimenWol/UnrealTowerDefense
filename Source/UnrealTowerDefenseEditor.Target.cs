using UnrealBuildTool;

public class UnrealTowerDefenseEditorTarget : TargetRules
{
    public UnrealTowerDefenseEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        CppStandard = CppStandardVersion.Latest;
        ExtraModuleNames.AddRange( new string[] { "UnrealTowerDefenseCore" } );
    }
}