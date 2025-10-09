#include "AI/TowerDefenseAIDirector.h"

#include "Assets/WaveListDataAsset.h"
#include "Assets/WaveSpawnDataAsset.h"

#include "Objects/WaveManager.h"

#include "Log.h"

void UTowerDefenseAIDirector::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    WaveManager = NewObject<UWaveManager>(this, UWaveManager::StaticClass(), TEXT("Wave Manager"));

    OnWaveStartedDelegateHandle = WaveManager->WaveStarted.AddUObject(this, &UTowerDefenseAIDirector::OnWaveStarted);
    OnWaveCompletedDelegateHandle = WaveManager->WaveCompleted.AddUObject(this, &UTowerDefenseAIDirector::OnWaveCompleted);
    OnWaveActorDiedDelegateHandle = WaveManager->ActorDied.AddUObject(this, &UTowerDefenseAIDirector::OnWaveActorDied);
    OnWaveActorReachedGoalDelegateHandle = WaveManager->ActorReachedGoal.AddUObject(this, &UTowerDefenseAIDirector::OnWaveActorReachedGoal);
}

void UTowerDefenseAIDirector::Deinitialize()
{
    Super::Deinitialize();

    if (WaveManager)
    {
        WaveManager->ActorDied.Remove(OnWaveActorDiedDelegateHandle);
        WaveManager->ActorReachedGoal.Remove(OnWaveActorReachedGoalDelegateHandle);
        WaveManager->WaveStarted.Remove(OnWaveStartedDelegateHandle);
        WaveManager->WaveCompleted.Remove(OnWaveCompletedDelegateHandle);

        WaveManager->Clear();
    }
}

bool UTowerDefenseAIDirector::StartNextWave()
{
    return WaveManager->StartNextWave();
}

void UTowerDefenseAIDirector::SetWaveListData(TObjectPtr<UWaveListDataAsset> WaveListData)
{
    WaveManager->SetWaveListData(WaveListData);
}

void UTowerDefenseAIDirector::SetWaveSpawnData(TSubclassOf<class UWaveSpawner> WaveSpawnerClass, TSubclassOf<class UWaveSpawnLocationsProvider> WaveSpawnLocationsProvider, TObjectPtr<class UWaveSpawnDataAsset> WaveSpawnData)
{
    WaveManager->SetWaveSpawnData(WaveSpawnerClass, WaveSpawnLocationsProvider, WaveSpawnData);
}

int32 UTowerDefenseAIDirector::GetNumWaves() const
{
    return WaveManager->GetNumWaves();
}

void UTowerDefenseAIDirector::OnWaveStarted(int32 StartedWaveIndex)
{
    if (WaveStarted.IsBound())
    {
        WaveStarted.Broadcast(StartedWaveIndex);
    }
}
void UTowerDefenseAIDirector::OnWaveCompleted(int32 CompletedWaveIndex)
{
    if (WaveCompleted.IsBound())
    {
        WaveCompleted.Broadcast(CompletedWaveIndex);
    }
}

void UTowerDefenseAIDirector::OnWaveActorDied(TScriptInterface<IWaveActor> WaveActor)
{
    if (WaveActorDied.IsBound())
    {
        WaveActorDied.Broadcast(WaveActor);
    }
}

void UTowerDefenseAIDirector::OnWaveActorReachedGoal(TScriptInterface<IWaveActor> WaveActor)
{
    if (WaveActorReachedGoal.IsBound())
    {
        WaveActorReachedGoal.Broadcast(WaveActor);
    }
}