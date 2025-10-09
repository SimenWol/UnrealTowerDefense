#include "OmniWaveAssets.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void FOmniWaveAssets::StartupModule()
{
    UE_LOG(LogOmniWaveAssets, Log, TEXT("OmniWaveAssets module starting up"));
}

void FOmniWaveAssets::ShutdownModule()
{
    UE_LOG(LogOmniWaveAssets, Log, TEXT("OmniWaveAssets module shutting down"));
}

IMPLEMENT_GAME_MODULE(FOmniWaveAssets, OmniWaveAssets);