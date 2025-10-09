#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FTowerDefenseAICore : public IModuleInterface
{
public:
    static inline FTowerDefenseAICore& Get()
    {
        return FModuleManager::LoadModuleChecked<FTowerDefenseAICore>("TowerDefenseAICore");
    }

    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("TowerDefenseAICore");
    }

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};