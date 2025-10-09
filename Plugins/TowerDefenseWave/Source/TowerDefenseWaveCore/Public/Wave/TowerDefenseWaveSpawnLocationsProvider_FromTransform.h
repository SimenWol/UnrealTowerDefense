#pragma once

#include "CoreMinimal.h"
#include "Objects/WaveSpawnLocationsProvider.h"
#include "TowerDefenseWaveSpawnLocationsProvider_FromTransform.generated.h"

/**
 * Provides spawn locations directly from a list of transforms (e.g. placed in a DataAsset).
 */
UCLASS()
class TOWERDEFENSEWAVECORE_API UTowerDefenseWaveSpawnLocationsProvider_FromTransform : public UWaveSpawnLocationsProvider
{
    GENERATED_BODY()

public:
    // List of transforms to spawn from.
    UPROPERTY(EditAnywhere, Category = "TowerDefenseCore")
    TArray<FTransform> Transforms;
    // Whether to loop when reaching the end.
    UPROPERTY(EditAnywhere, Category = "TowerDefenseCore")
    bool bLoop = false;

public:
    // Initializes internal state (resets index, etc.)
    virtual void Initialize() override;

    // Loads transform data from a WaveSpawnDataAsset (expects UTowerDefenseSpawnDataAsset_FromTransform).
    virtual void InitializeFromAsset(TObjectPtr<UWaveSpawnDataAsset> WaveSpawnAssetData) override;

    // Gets the next spawn transform; returns false if none available.
    virtual bool GetNextSpawnTransform(FTransform& Out) override;

    // Returns number of available spawn points.
    virtual int32 NumSpawnPoints() const override;

    // Returns all available spawn transforms.
    virtual TArray<FTransform> GetAllSpawnTransforms() const override;

private:
    // Index tracking next spawn location.
    int32 NextIndex = 0;
};
