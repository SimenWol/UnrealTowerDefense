#pragma once

#include "CoreMinimal.h"
#include "Assets/WaveSpawnDataAsset.h"

#include "TowerDefenseSpawnDataAsset_FromLine.generated.h"

UCLASS()
class TOWERDEFENSEWAVECORE_API UTowerDefenseSpawnDataAsset_FromLine : public UWaveSpawnDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category="TowerDefenseCore|Wave")
    FVector Start = FVector::ZeroVector;
    UPROPERTY(EditAnywhere, Category="TowerDefenseCore|Wave")
    FVector End = FVector(1000, 0, 0);
    UPROPERTY(EditAnywhere, Category="TowerDefenseCore|Wave", meta=(ClampMin="1"))
    int32 Count = 5;
    UPROPERTY(EditAnywhere, Category="TowerDefenseCore|Wave")
    bool bIncludeEndpoints = true;
    UPROPERTY(EditAnywhere, Category="TowerDefenseCore|Wave")
    bool bAlignRotationToDirection = true;
    UPROPERTY(EditAnywhere, Category="TowerDefenseCore|Wave")
    bool bLoop = true;
};