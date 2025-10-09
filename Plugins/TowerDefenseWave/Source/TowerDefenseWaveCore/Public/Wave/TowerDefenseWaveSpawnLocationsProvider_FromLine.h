#pragma once

#include "CoreMinimal.h"
#include "Objects/WaveSpawnLocationsProvider.h"
#include "TowerDefenseWaveSpawnLocationsProvider_FromLine.generated.h"

/**
 * Provides spawn locations evenly distributed along a line.
 */
UCLASS()
class TOWERDEFENSEWAVECORE_API UTowerDefenseWaveSpawnLocationsProvider_FromLine : public UWaveSpawnLocationsProvider
{
    GENERATED_BODY()

public:
    // Line start and end positions.
    UPROPERTY(EditAnywhere, Category = "TowerDefenseCore")
    FVector Start = FVector::ZeroVector;
    UPROPERTY(EditAnywhere, Category = "TowerDefenseCore")
    FVector End = FVector::ZeroVector;
    // Number of spawn points along the line.
    UPROPERTY(EditAnywhere, Category = "TowerDefenseCore")
    int32 Count = 0;
    // Whether endpoints are included in the distribution.
    UPROPERTY(EditAnywhere, Category = "TowerDefenseCore")
    bool bIncludeEndpoints = true;
    // Whether rotations should be aligned to the line direction.
    UPROPERTY(EditAnywhere, Category = "TowerDefenseCore")
    bool bAlignRotationToDirection = false;
    // Whether iteration loops when reaching the end.
    UPROPERTY(EditAnywhere, Category = "TowerDefenseCore")
    bool bLoop = false;

public:
    // Initializes internal state (builds cached points).
    virtual void Initialize() override;

    // Loads line spawn data from a WaveSpawnDataAsset (expects UTowerDefenseSpawnDataAsset_FromLine).
    virtual void InitializeFromAsset(TObjectPtr<UWaveSpawnDataAsset> WaveSpawnAssetData) override;

    // Gets the next spawn transform; returns false if none available.
    virtual bool GetNextSpawnTransform(FTransform& Out) override;

    // Returns number of available spawn points.
    virtual int32 NumSpawnPoints() const override;

    // Returns all available spawn transforms.
    virtual TArray<FTransform> GetAllSpawnTransforms() const override;

private:
    // Rebuilds cached spawn points along the line.
    bool BuildPoints();

private:
    // Cached computed transforms.
    UPROPERTY(Transient)
    TArray<FTransform> Cached;

    // Index tracking next spawn location.
    int32 NextIndex = 0;
};
