#include "OmniWaveCore.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void FOmniWaveCore::StartupModule()
{
	UE_LOG(LogOmniWaveCore, Log, TEXT("OmniWaveCore module starting up"));
}

void FOmniWaveCore::ShutdownModule()
{
	UE_LOG(LogOmniWaveCore, Log, TEXT("OmniWaveCore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FOmniWaveCore, OmniWaveCore, "OmniWaveCore");
