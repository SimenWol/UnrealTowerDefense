#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/Object.h"
#include "IWaveActor.generated.h"

/**
 * This is implemented by any actor that can be spawned in a wave.
 * It defines how the WaveManager interacts with spawned enemies:
 *  - Binding to death / reaching goal events
 *  - Reuse and destruction
 *  - Teleporting to spawn points
 */
UINTERFACE(BlueprintType)
class OMNIWAVECORE_API UWaveActor : public UInterface
{
    GENERATED_BODY()
};

class OMNIWAVECORE_API IWaveActor
{
    GENERATED_BODY()

public:
    // Bind to lifecycle events. Return handles so we can unbind safely.
    virtual FDelegateHandle BindOnDied(const FSimpleDelegate& Callback) = 0;
    virtual void UnbindOnDied(FDelegateHandle Handle) = 0;

    virtual FDelegateHandle BindOnReachedGoal(const FSimpleDelegate& Callback) = 0;
    virtual void UnbindOnReachedGoal(FDelegateHandle Handle) = 0;

    // Called when the manager wants this actor to be reused.
    virtual void RestartForReuse() = 0;
    // Called when the actor is no longer needed in this wave.
    virtual void DestroyWaveActor() = 0;

    // Teleport the actor to the specified spawn transform.
    virtual void WaveTeleportToSpawnTransform(const FTransform& Transform) = 0;
};