#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveListDataAsset.generated.h"

/**
 * Defines how many of a specific enemy type should spawn in a wave.
 */
USTRUCT(BlueprintType)
struct FWaveEntry
{
    GENERATED_BODY()

    // Which type of actor to spawn (must implement IWaveActor)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "WaveActor"))
    TSubclassOf<AActor> WaveActorType;

    // How many of this type to spawn
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1"))
    int32 Amount = 1;
};

/**
 * Defines a custom spawn sequence when interleaving different enemy types.
 */
USTRUCT(BlueprintType)
struct FWaveInterleave
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "WaveActor"))
    TSubclassOf<AActor> WaveActorType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1"))
    int32 Count = 1;
};

/**
 * Defines a complete wave configuration.
 * Contains multiple FWaveEntry definitions and optionally an interleave sequence.
 */
USTRUCT(BlueprintType)
struct FWave
{
    GENERATED_BODY()

    // How quickly enemies spawn (seconds between spawns)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.01"))
    float SpawnRate = 0.01f;

    // The list of enemy types and amounts
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FWaveEntry> Entries;

    // Whether to interleave between types
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bInterleave = false;

    // Optional custom sequence for interleaving
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bInterleave"))
    TArray<FWaveInterleave> Sequence;
};

/**
 * A data asset that holds multiple waves (designers can fill this in the editor).
 */
UCLASS(BlueprintType)
class OMNIWAVEASSETS_API UWaveListDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FWave> Waves;

    int32 GetNumWaves() const { return Waves.Num(); }
};
