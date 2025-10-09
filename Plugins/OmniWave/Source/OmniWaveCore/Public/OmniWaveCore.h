#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FOmniWaveCore : public IModuleInterface
{
public:
	static inline FOmniWaveCore& Get()
	{
		return FModuleManager::LoadModuleChecked<FOmniWaveCore>("OmniWaveCore");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("OmniWaveCore");
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};