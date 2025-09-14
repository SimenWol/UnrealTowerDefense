#pragma once
    
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class UnrealTowerDefenseCore : public IModuleInterface
{
public:
    static inline UnrealTowerDefenseCore& Get()
    {
        return FModuleManager::LoadModuleChecked<UnrealTowerDefenseCore>("UnrealTowerDefenseCore");
    }

    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("UnrealTowerDefenseCore");
    }

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};