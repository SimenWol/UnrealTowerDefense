#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TowerDefenseAIDirector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIDirectorWaveDelegate, int32, WaveIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIDirectorWaveActorDelegate, TScriptInterface<class IWaveActor>, WaveActor);

UCLASS()
class TOWERDEFENSEAICORE_API UTowerDefenseAIDirector : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    /** UWorldSubsystem interface */
    void Initialize(FSubsystemCollectionBase& Collection) override;
    void Deinitialize() override;

public:
    bool StartNextWave();

    void SetWaveListData(TObjectPtr<class UWaveListDataAsset> WaveListData);
    void SetWaveSpawnData(TSubclassOf<class UWaveSpawner> WaveSpawnerClass, TSubclassOf<class UWaveSpawnLocationsProvider> WaveSpawnLocationsProvider, TObjectPtr<class UWaveSpawnDataAsset> WaveSpawnData);

public:
    int32 GetNumWaves() const;

public:
    UPROPERTY(BlueprintAssignable, Category = "TowerDefenseCore|AI")
    FAIDirectorWaveDelegate WaveStarted;
    UPROPERTY(BlueprintAssignable, Category = "TowerDefenseCore|AI")
    FAIDirectorWaveDelegate WaveCompleted;

    UPROPERTY(BlueprintAssignable, Category = "TowerDefenseCore|AI")
    FAIDirectorWaveActorDelegate WaveActorDied;
    UPROPERTY(BlueprintAssignable, Category = "TowerDefenseCore|AI")
    FAIDirectorWaveActorDelegate WaveActorReachedGoal;

private:
    void OnWaveStarted(int32 StartedWaveIndex);
    void OnWaveCompleted(int32 CompletedWaveIndex);
    void OnWaveActorDied(TScriptInterface<class IWaveActor> WaveActor);
    void OnWaveActorReachedGoal(TScriptInterface<class IWaveActor> WaveActor);

private:
    UPROPERTY()
    TObjectPtr<class UWaveManager> WaveManager;

    FDelegateHandle OnWaveStartedDelegateHandle;
    FDelegateHandle OnWaveCompletedDelegateHandle;
    FDelegateHandle OnWaveActorDiedDelegateHandle;
    FDelegateHandle OnWaveActorReachedGoalDelegateHandle;
};