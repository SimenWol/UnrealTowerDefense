#include "Wave/TowerDefenseWaveSpawnLocationsProvider_FromLine.h"
#include "Wave/Assets/TowerDefenseSpawnDataAsset_FromLine.h"

void UTowerDefenseWaveSpawnLocationsProvider_FromLine::Initialize()
{
    BuildPoints();
}

void UTowerDefenseWaveSpawnLocationsProvider_FromLine::InitializeFromAsset(TObjectPtr<UWaveSpawnDataAsset> WaveSpawnAssetData)
{
    UTowerDefenseSpawnDataAsset_FromLine* LineData = Cast<UTowerDefenseSpawnDataAsset_FromLine>(WaveSpawnAssetData.Get());

    if (LineData)
    {
        Start = LineData->Start;
        End = LineData->End;
        Count = LineData->Count;
        bIncludeEndpoints = LineData->bIncludeEndpoints;
        bAlignRotationToDirection = LineData->bAlignRotationToDirection;
        bLoop = LineData->bLoop;
    }

    Initialize();
}

bool UTowerDefenseWaveSpawnLocationsProvider_FromLine::GetNextSpawnTransform(FTransform& Out)
{
    if (Cached.Num() == 0) return false;
    
    const int32 Index = FMath::Clamp(NextIndex, 0, Cached.Num()-1);
    Out = Cached[Index];
    NextIndex = bLoop ? (Index + 1) % Cached.Num() : FMath::Min(Index + 1, Cached.Num() - 1);
    return true;
}

int32 UTowerDefenseWaveSpawnLocationsProvider_FromLine::NumSpawnPoints() const
{
    return Cached.Num();
}

TArray<FTransform> UTowerDefenseWaveSpawnLocationsProvider_FromLine::GetAllSpawnTransforms() const
{
    return Cached;
}

bool UTowerDefenseWaveSpawnLocationsProvider_FromLine::BuildPoints()
{
    Cached.Reset();
    if (Count <= 0) return false;

    const FVector Dir = (End - Start);
    const float Len = Dir.Size();
    if (Len <= KINDA_SMALL_NUMBER) return false;

    const int32 N = Count;
    const int32 Den = bIncludeEndpoints ? (N - 1) : (N + 1);
    const FVector Step = Dir / float(FMath::Max(Den, 1));
    const int32 StartIdx = bIncludeEndpoints ? 0 : 1;

    Cached.Reserve(N);
    for (int32 i = 0; i < N; ++i)
    {
        const FVector P = Start + Step * float(StartIdx + i);
        const FRotator R = bAlignRotationToDirection ? Dir.Rotation() : FRotator::ZeroRotator;
        Cached.Emplace(R, P);
    }
    NextIndex = 0;
    return true;
}