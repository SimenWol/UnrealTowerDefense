#include "OmniCameraCore.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void FOmniCameraCore::StartupModule()
{
    UE_LOG(LogOmniCameraCore, Log, TEXT("OmniCameraCore module starting up"));
}

void FOmniCameraCore::ShutdownModule()
{
    UE_LOG(LogOmniCameraCore, Log, TEXT("OmniCameraCore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FOmniCameraCore, OmniCameraCore, "OmniCameraCore");
