#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FOmniCameraCore : public IModuleInterface
{
public:
    static inline FOmniCameraCore& Get()
    {
        return FModuleManager::LoadModuleChecked<FOmniCameraCore>("OmniCameraCore");
    }

    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("OmniCameraCore");
    }

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};