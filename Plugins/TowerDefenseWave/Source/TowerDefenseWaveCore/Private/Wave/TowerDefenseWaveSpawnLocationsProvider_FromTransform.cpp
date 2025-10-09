#include "Wave/TowerDefenseWaveSpawnLocationsProvider_FromTransform.h"
#include "Wave/Assets/TowerDefenseSpawnDataAsset_FromTransform.h"

void UTowerDefenseWaveSpawnLocationsProvider_FromTransform::Initialize()
{
    NextIndex = 0;
}

void UTowerDefenseWaveSpawnLocationsProvider_FromTransform::InitializeFromAsset(TObjectPtr<UWaveSpawnDataAsset> WaveSpawnAssetData)
{
    UTowerDefenseSpawnDataAsset_FromTransform* TransformAsset = Cast<UTowerDefenseSpawnDataAsset_FromTransform>(WaveSpawnAssetData);
    if (TransformAsset)
    {
        Transforms = TransformAsset->Transforms;
        bLoop = TransformAsset->bLoop;
    }

    Initialize();
}

bool UTowerDefenseWaveSpawnLocationsProvider_FromTransform::GetNextSpawnTransform(FTransform& Out)
{
    if (Transforms.Num() == 0) return false;

    const int32 Index = FMath::Clamp(NextIndex, 0, Transforms.Num()-1);
    Out = Transforms[Index];
    NextIndex = bLoop ? (Index + 1) % Transforms.Num() : FMath::Min(Index + 1, Transforms.Num() - 1);
    return true;
}

int32 UTowerDefenseWaveSpawnLocationsProvider_FromTransform::NumSpawnPoints() const
{
    return Transforms.Num();
}

TArray<FTransform> UTowerDefenseWaveSpawnLocationsProvider_FromTransform::GetAllSpawnTransforms() const
{
    return Transforms;
}