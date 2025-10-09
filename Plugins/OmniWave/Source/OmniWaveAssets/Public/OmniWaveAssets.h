#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FOmniWaveAssets : public IModuleInterface
{
public:
    static inline FOmniWaveAssets& Get()
    {
        return FModuleManager::LoadModuleChecked<FOmniWaveAssets>("OmniWaveAssets");
    }

    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("OmniWaveAssets");
    }

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};