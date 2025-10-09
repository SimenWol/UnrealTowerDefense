#pragma once

#include "UObject/Object.h"
#include "WaveSpawnLocationsProvider.generated.h"

/**
 * Abstract class that provides spawn locations.
 * Implementations decide how/where to place enemies:
 *  - From predefined transforms
 *  - From a line
 *  - From checkpoints
 */
UCLASS(BlueprintType, Abstract)
class OMNIWAVECORE_API UWaveSpawnLocationsProvider : public UObject
{
    GENERATED_BODY()

public:
    // Called once at startup
    virtual void Initialize() {}

    // Called when initializing from a data asset
    virtual void InitializeFromAsset(TObjectPtr<class UWaveSpawnDataAsset> WaveSpawnAssetData) {}

    // Return the next spawn transform (true if valid, false if not)
    virtual bool GetNextSpawnTransform(FTransform& OutTransform) { return false; }

    // Number of spawn points available
    virtual int32 NumSpawnPoints() const { return 0; }

    // Return all possible spawn transforms
    virtual TArray<FTransform> GetAllSpawnTransforms() const { return TArray<FTransform>(); }
};
