#pragma once

#include "CoreMinimal.h"
#include "TowerDefenseWaveInfo.generated.h"

/**
 * Struct that bundles together all data and classes needed
 * to spawn enemy waves in the game.
 *
 * Designers can set this up in the editor:
 *  - WaveListData: which waves exist
 *  - WaveSpawnData: how to spawn enemies
 *  - WaveSpawnLocationsProviderClass: where enemies can spawn
 *  - WaveSpawnerClass: which spawner implementation to use
 */
USTRUCT(BlueprintType)
struct FWaveInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TowerDefenseCore")
    TObjectPtr<class UWaveListDataAsset> WaveListData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TowerDefenseCore")
    TObjectPtr<class UWaveSpawnDataAsset> WaveSpawnData;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TowerDefenseCore")
    TSubclassOf<class UWaveSpawnLocationsProvider> WaveSpawnLocationsProviderClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TowerDefenseCore")
    TSubclassOf<class UWaveSpawner> WaveSpawnerClass;
};