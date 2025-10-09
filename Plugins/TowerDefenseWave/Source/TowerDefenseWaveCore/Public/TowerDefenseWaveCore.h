#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FTowerDefenseWaveCore : public IModuleInterface
{
public:
    static inline FTowerDefenseWaveCore& Get()
    {
        return FModuleManager::LoadModuleChecked<FTowerDefenseWaveCore>("TowerDefenseWaveCore");
    }

    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("TowerDefenseWaveCore");
    }

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};