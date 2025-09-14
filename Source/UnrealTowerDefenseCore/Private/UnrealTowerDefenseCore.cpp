#include "UnrealTowerDefenseCore.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void UnrealTowerDefenseCore::StartupModule()
{
    UE_LOG(LogUnrealTowerDefenseCore, Log, TEXT("UnrealTowerDefenseCore module starting up"));
}

void UnrealTowerDefenseCore::ShutdownModule()
{
    UE_LOG(LogUnrealTowerDefenseCore, Log, TEXT("UnrealTowerDefenseCore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(UnrealTowerDefenseCore, UnrealTowerDefenseCore, "UnrealTowerDefenseCore");