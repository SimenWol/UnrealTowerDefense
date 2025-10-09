#include "Objects/WaveManager.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Log.h"

void UWaveManager::SetWaveListData(TObjectPtr<UWaveListDataAsset> InWaveList) 
{
    WaveList = InWaveList; 
}

void UWaveManager::SetWaveSpawnData(TSubclassOf<UWaveSpawner> WaveSpawnerClass, TSubclassOf<UWaveSpawnLocationsProvider> WaveSpawnLocationsProvider, TObjectPtr<UWaveSpawnDataAsset> InSpawnData) 
{
    Spawner = NewObject<UWaveSpawner>(this, WaveSpawnerClass);
    Spawner->SetWaveSpawnData(WaveSpawnLocationsProvider, InSpawnData);
}

bool UWaveManager::StartNextWave()
{
    if (!WaveList || !Spawner)
    {
        UE_LOG(LogOmniWaveCore, Warning, TEXT("WaveManager missing dependencies (WaveList or Spawner)."));
        return false;
    }

    const int32 NumWaves = WaveList->GetNumWaves();
    if (CurrentWave >= NumWaves)
    {
        UE_LOG(LogOmniWaveCore, Warning, TEXT("No more waves to start."));
        return false;
    }

    SpawnQueue.Empty();
    SpawnQueueIndex = 0;
    CurrentWaveSpawnRate = 1.0f;

    if (!BuildSpawnOrder(WaveList->Waves[CurrentWave]) || SpawnQueue.Num() == 0)
    {
        UE_LOG(LogOmniWaveCore, Warning, TEXT("Wave %d has no spawn entries."), CurrentWave);
        return false;
    }

    // Fire wave started
    WaveStarted.Broadcast(CurrentWave);

    // Spawn first immediately
    SpawnNextFromQueue();

    // Schedule remaining
    if (SpawnQueueIndex < SpawnQueue.Num())
    {
        GetWorld()->GetTimerManager().SetTimer(
            SpawnTimerHandle,
            this,
            &UWaveManager::OnSpawnTimerFinished,
            FMath::Max(0.01f, CurrentWaveSpawnRate),
            true);
    }

    return true;
}

int32 UWaveManager::GetNumWaves() const
{
    return WaveList ? WaveList->GetNumWaves() : 0;
}

void UWaveManager::Clear()
{
    // Stop timers
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(SpawnTimerHandle);
    }

    // Unbind per-actor delegates and clear references
    for (auto& Data : ActiveActors)
    {
        if (Data.WaveActor)
        {
            if (Data.DiedHandle.IsValid())        { Data.WaveActor->UnbindOnDied(Data.DiedHandle); }
            if (Data.ReachedGoalHandle.IsValid()) { Data.WaveActor->UnbindOnReachedGoal(Data.ReachedGoalHandle); }
        }
    }

    ActiveActors.Empty();
    RecyclePool.Empty();
}

void UWaveManager::OnSpawnTimerFinished()
{
    UE_LOG(LogOmniWaveCore, Log, TEXT("OnSpawnTimerFinished tick"));

    if (RecyclePool.Num() > 0)
    {
        // Reuse an existing actor by teleporting and restarting it.
        TScriptInterface<IWaveActor> ActorToActivate = RecyclePool[0];
        if (ActorToActivate && Spawner && Spawner->TeleportToNextSpawnTransform(ActorToActivate))
        {
            ActorToActivate->RestartForReuse();
            RecyclePool.RemoveAt(0);
        }
    }
    else if (SpawnQueueIndex < SpawnQueue.Num())
    {
        SpawnNextFromQueue();
    }
    else
    {
        // No more to spawn; clear timer
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
    }
}

void UWaveManager::OnActorDied(UObject* ActorObj)
{
    const int32 Index = ActiveActors.IndexOfByPredicate(
        [ActorObj](const FTrackedActor& Data)
        {
            return Data.WaveActor.GetObject() == ActorObj;
        });

    if (Index != INDEX_NONE)
    {
        FTrackedActor& Data = ActiveActors[Index];

        UE_LOG(LogOmniWaveCore, Log, TEXT("WaveActor (%s) died"), *ActorObj->GetName());

        if (ActorDied.IsBound())
        {
            ActorDied.Broadcast(Data.WaveActor);
        }

        // Unbind delegates
        if (Data.WaveActor)
        {
            if (Data.DiedHandle.IsValid())       { Data.WaveActor->UnbindOnDied(Data.DiedHandle); }
            if (Data.ReachedGoalHandle.IsValid()){ Data.WaveActor->UnbindOnReachedGoal(Data.ReachedGoalHandle); }
        }

        // Destroy the actor
        if (Data.WaveActor) { Data.WaveActor->DestroyWaveActor(); }

        ActiveActors.RemoveAt(Index);

        if (ActiveActors.IsEmpty())
        {
            if (WaveCompleted.IsBound())
            {
                const int32 CompletedWaveIndex = CurrentWave;
                WaveCompleted.Broadcast(CompletedWaveIndex);
                ++CurrentWave;
            }
        }
    }
}

void UWaveManager::OnActorReachedGoal(UObject* ActorObj)
{
    const int32 Index = ActiveActors.IndexOfByPredicate(
        [ActorObj](const FTrackedActor& Data)
        {
            return Data.WaveActor.GetObject() == ActorObj;
        });

    if (Index != INDEX_NONE)
    {
        TScriptInterface<IWaveActor> ActorIface = ActiveActors[Index].WaveActor;

        UE_LOG(LogOmniWaveCore, Log, TEXT("WaveActor (%s) reached goal, NumFinishedPath: %d"), *ActorObj->GetName(), RecyclePool.Num());

        // We keep it around for reuse instead of destroying.
        if (ActorIface)
        {
            RecyclePool.Add(ActorIface);
        }

        if (ActorReachedGoal.IsBound())
        {
            ActorReachedGoal.Broadcast(ActorIface);
        }

        // Ensure timer runs so we can keep reusing while there is demand
        if (!GetWorld()->GetTimerManager().IsTimerActive(SpawnTimerHandle))
        {
            GetWorld()->GetTimerManager().SetTimer(
                SpawnTimerHandle,
                this,
                &UWaveManager::OnSpawnTimerFinished,
                FMath::Max(0.01f, CurrentWaveSpawnRate),
                true);
        }
    }
}

bool UWaveManager::SpawnNextFromQueue()
{
    if (SpawnQueueIndex >= SpawnQueue.Num())
    {
        return false;
    }

    if (!Spawner)
    {
        return false;
    }

    TSubclassOf<AActor> Type = SpawnQueue[SpawnQueueIndex++];
    AActor* NewActor = Spawner->Spawn(Type);
    TScriptInterface<IWaveActor> NewWaveActor = TScriptInterface<IWaveActor>(NewActor);
    if (NewWaveActor)
    {
        // Bind lifecycle events to manager handlers
        FTrackedActor Tracked;
        Tracked.WaveActor = NewWaveActor;
        Tracked.DiedHandle = NewWaveActor->BindOnDied(FSimpleDelegate::CreateUObject(this, &UWaveManager::OnActorDied, NewWaveActor.GetObject()));
        Tracked.ReachedGoalHandle = NewWaveActor->BindOnReachedGoal(FSimpleDelegate::CreateUObject(this, &UWaveManager::OnActorReachedGoal, NewWaveActor.GetObject()));

        ActiveActors.Add(MoveTemp(Tracked));

        UE_LOG(LogOmniWaveCore, Log, TEXT("WaveActor (%s) Spawned, NumSpawned: %d"), *NewWaveActor.GetObject()->GetName(), SpawnQueueIndex);
        return true;
    }

    UE_LOG(LogOmniWaveCore, Warning, TEXT("Actor not spawned; WaveActor interface not available from spawner."));
    return false;
}

bool UWaveManager::BuildSpawnOrder(const struct FWave& Wave)
{
     if (!Wave.bInterleave)
     {
         for (const auto& Entry : Wave.Entries)
         {
             for (int32 i = 0; i < Entry.Amount; ++i)
             {
                 SpawnQueue.Add(Entry.WaveActorType);
             }
         }
     }
     else if (Wave.Sequence.Num() > 0)
     {
         for (const auto& Step : Wave.Sequence)
         {
             for (int32 i = 0; i < Step.Count; ++i)
             {
                 SpawnQueue.Add(Step.WaveActorType);
             }
         }
     }
     else
     {
         // Default interleave: cycle one of each until all amounts exhausted
         TArray<int32> Remaining;
         Remaining.Reserve(Wave.Entries.Num());
         for (const auto& Entry : Wave.Entries)
         {
             Remaining.Add(Entry.Amount);
         }
         
         bool bStill = true;
         while (bStill)
         {
             bStill = false;
             for (int32 i = 0; i < Wave.Entries.Num(); ++i)
             {
                 if (Remaining[i] > 0)
                 {
                     SpawnQueue.Add(Wave.Entries[i].WaveActorType);
                     Remaining[i]--;
                     bStill = true;
                 }
             }
         }
     }
    
     if (SpawnQueue.Num() == 0)
     {
         return false;
     }
    
    
    return true;
}