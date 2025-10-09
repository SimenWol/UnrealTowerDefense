#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Actors/IWaveActor.h"
#include "Objects/WaveSpawner.h"
#include "Assets/WaveListDataAsset.h"
#include "WaveManager.generated.h"

// Broadcasts wave index (e.g. when started or completed)
DECLARE_MULTICAST_DELEGATE_OneParam(FWaveManagerDelegate, int32);
// Broadcasts a wave actor involved in an event (died or reached goal)
DECLARE_MULTICAST_DELEGATE_OneParam(FWaveManagerActorDelegate, TScriptInterface<IWaveActor>);

/**
 * Coordinates wave progression:
 *  - Tells the spawner what to spawn
 *  - Tracks active enemies
 *  - Emits events when enemies die or reach the goal
 *  - Handles progression between waves
 */
UCLASS()
class OMNIWAVECORE_API UWaveManager : public UObject
{
    GENERATED_BODY()

public:
    // The spawner responsible for creating actors
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OmniWaveCore") 
    TObjectPtr<class UWaveSpawner> Spawner;

    // The list of waves (data-driven, editable by designers)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OmniWaveCore") 
    TObjectPtr<class UWaveListDataAsset> WaveList;

public:
    bool StartNextWave();

    // Assign wave data assets and spawner setup
    void SetWaveListData(TObjectPtr<class UWaveListDataAsset> InWaveList);
    void SetWaveSpawnData(TSubclassOf<class UWaveSpawner> WaveSpawnerClass, TSubclassOf<class UWaveSpawnLocationsProvider> WaveSpawnLocationsProvider, TObjectPtr<class UWaveSpawnDataAsset> InSpawnData);

    int32 GetNumWaves() const;

    void Clear();

    // Events (subscribed to by GameMode or other systems)
    FWaveManagerDelegate WaveStarted;
    FWaveManagerDelegate WaveCompleted;
    FWaveManagerActorDelegate ActorDied;
    FWaveManagerActorDelegate ActorReachedGoal;

private:
    // Internal event handlers
    void OnSpawnTimerFinished();
    void OnActorDied(UObject* ActorObj);
    void OnActorReachedGoal(UObject* ActorObj);

    // Spawn helpers
    bool SpawnNextFromQueue();
    bool BuildSpawnOrder(const struct FWave& Wave);

private:
    int32 CurrentWave = 0;   // Index of current wave

    // Queue of what to spawn
    TArray<TSubclassOf<AActor>> SpawnQueue;
    int32 SpawnQueueIndex = 0;
    float CurrentWaveSpawnRate = 1.0f;

    // Timer for spawning enemies over time
    FTimerHandle SpawnTimerHandle;

    // Tracks active actors + their bound delegate handles
    struct FTrackedActor
    {
        TScriptInterface<IWaveActor> WaveActor;

        FDelegateHandle DiedHandle;
        FDelegateHandle ReachedGoalHandle;
    };

    TArray<FTrackedActor> ActiveActors;
    // Pool of actors available for reuse
    TArray<TScriptInterface<IWaveActor>> RecyclePool;
};
