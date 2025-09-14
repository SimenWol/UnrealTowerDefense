using UnrealBuildTool;
    
public class UnrealTowerDefenseTarget : TargetRules
{
    public UnrealTowerDefenseTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        CppStandard = CppStandardVersion.Latest;
        ExtraModuleNames.AddRange( new string[] { "UnrealTowerDefenseCore" } );
    }
}