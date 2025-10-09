#include "Objects/WaveSpawner.h"

#include "Actors/IWaveActor.h"

#include "Log.h"

void UWaveSpawner::SetWaveSpawnData(TSubclassOf<class UWaveSpawnLocationsProvider> InProviderClass, TObjectPtr<class UWaveSpawnDataAsset> SpawnDataAsset)
{
    if (ensure(InProviderClass))
    {
        SpawnLocationsProviderInstance = NewObject<UWaveSpawnLocationsProvider>(this, InProviderClass);

        if(SpawnDataAsset)
        {
            SpawnLocationsProviderInstance->InitializeFromAsset(SpawnDataAsset);
        }
        else
        {
            SpawnLocationsProviderInstance->Initialize();
        }
    }
    else
    {
        SpawnLocationsProviderInstance = nullptr;
        UE_LOG(LogOmniWaveCore, Warning, TEXT("Invalid Spawn Location Provider Instance given to CreateSpawnLocationProviderInstance."));
    }
}

AActor* UWaveSpawner::Spawn(TSubclassOf<AActor> ActorClass)
{
    if(!ActorClass)
    {
        UE_LOG(LogOmniWaveCore, Warning, TEXT("Invalid Actor Class given to Spawn."));
        return nullptr;
    }

    if (!ActorClass->ImplementsInterface(UWaveActor::StaticClass()))
    {
        UE_LOG(LogOmniWaveCore, Warning, TEXT("Actor Class %s does not implement IWaveActor interface."), *ActorClass->GetName());
        return nullptr;
    }

    if(!SpawnLocationsProviderInstance)
    {
        UE_LOG(LogOmniWaveCore, Warning, TEXT("No Spawn Location Provider available."));
        return nullptr;
    }

    FTransform NextTransform;
    if(SpawnLocationsProviderInstance->GetNextSpawnTransform(NextTransform))
    {
        AActor* WaveActor = GetWorld()->SpawnActor<AActor>(ActorClass, NextTransform);
        if(WaveActor)
        {
            UE_LOG(LogOmniWaveCore, Log, TEXT("Actor spawned successfully."));
        }
        else
        {
            UE_LOG(LogOmniWaveCore, Warning, TEXT("Actor not spawned; WaveActor interface not available from spawner."));
        }

        return WaveActor;
    }

    UE_LOG(LogOmniWaveCore, Warning, TEXT("No spawn transform available from provider."));
    return nullptr;
}

bool UWaveSpawner::TeleportToNextSpawnTransform(TScriptInterface<IWaveActor> InActor)
{
    if(!InActor)
    {
        UE_LOG(LogOmniWaveCore, Warning, TEXT("Invalid IWaveActor given to Teleport."));
        return false;
    }

    if(!SpawnLocationsProviderInstance)
    {
        UE_LOG(LogOmniWaveCore, Warning, TEXT("No Spawn Location Provider available."));
        return false;
    }

    FTransform NextTransform;
    if(SpawnLocationsProviderInstance->GetNextSpawnTransform(NextTransform))
    {
        InActor->WaveTeleportToSpawnTransform(NextTransform);
        return true;
    }

    UE_LOG(LogOmniWaveCore, Warning, TEXT("No spawn transform available from provider."));
    return false;
}