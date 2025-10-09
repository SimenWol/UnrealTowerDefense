#include "TowerDefenseWaveCore.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void FTowerDefenseWaveCore::StartupModule()
{
    UE_LOG(LogTowerDefenseWaveCore, Log, TEXT("TowerDefenseWaveCore module starting up"));
}

void FTowerDefenseWaveCore::ShutdownModule()
{
    UE_LOG(LogTowerDefenseWaveCore, Log, TEXT("TowerDefenseWaveCore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FTowerDefenseWaveCore, TowerDefenseWaveCore, "TowerDefenseWaveCore");
