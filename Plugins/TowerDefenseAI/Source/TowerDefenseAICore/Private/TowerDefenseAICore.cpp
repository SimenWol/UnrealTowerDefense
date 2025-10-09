#include "TowerDefenseAICore.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void FTowerDefenseAICore::StartupModule()
{
    UE_LOG(LogTowerDefenseAICore, Log, TEXT("TowerDefenseAICore module starting up"));
}

void FTowerDefenseAICore::ShutdownModule()
{
    UE_LOG(LogTowerDefenseAICore, Log, TEXT("TowerDefenseAICore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FTowerDefenseAICore, TowerDefenseAICore, "TowerDefenseAICore");
