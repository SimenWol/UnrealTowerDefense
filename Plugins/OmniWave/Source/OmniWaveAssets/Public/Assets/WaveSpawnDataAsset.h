#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveSpawnDataAsset.generated.h"

/**
 * Base class for spawn-specific configuration.
 * Different spawn location providers can subclass this
 * to hold the data they need (line, circle, transforms, etc.).
 */
UCLASS(BlueprintType, Abstract)
class OMNIWAVEASSETS_API UWaveSpawnDataAsset : public UDataAsset
{
    GENERATED_BODY()
};
