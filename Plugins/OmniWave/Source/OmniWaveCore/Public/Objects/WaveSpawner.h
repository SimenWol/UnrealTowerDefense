#pragma once

#include "CoreMinimal.h"
#include "Objects/WaveSpawnLocationsProvider.h"
#include "WaveSpawner.generated.h"

/**
 * Handles the actual spawning of enemies into the world.
 * Works together with a WaveSpawnLocationsProvider to know where to place them.
 */
UCLASS(BlueprintType)
class OMNIWAVECORE_API UWaveSpawner : public UObject
{
    GENERATED_BODY()

public:
    // Configure with a spawn location provider and data
    void SetWaveSpawnData(TSubclassOf<class UWaveSpawnLocationsProvider> InProvider, TObjectPtr<class UWaveSpawnDataAsset> SpawnDataAsset);

    // Spawn an actor of the given class
    virtual class AActor* Spawn(TSubclassOf<class AActor> ActorClass);

    // Move an existing actor to the next spawn point
    virtual bool TeleportToNextSpawnTransform(TScriptInterface<class IWaveActor> ActorObj);

private:
    // The active spawn location provider (e.g. FromLine, FromTransforms, etc.)
    UPROPERTY()
    TObjectPtr<UWaveSpawnLocationsProvider> SpawnLocationsProviderInstance = nullptr;
};
