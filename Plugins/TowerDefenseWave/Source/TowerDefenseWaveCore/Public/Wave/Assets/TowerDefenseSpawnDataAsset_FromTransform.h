#pragma once

#include "CoreMinimal.h"
#include "Assets/WaveSpawnDataAsset.h"

#include "TowerDefenseSpawnDataAsset_FromTransform.generated.h"

UCLASS()
class TOWERDEFENSEWAVECORE_API UTowerDefenseSpawnDataAsset_FromTransform : public UWaveSpawnDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category="TowerDefenseCore|Wave")
    TArray<FTransform> Transforms;
    UPROPERTY(EditAnywhere, Category="TowerDefenseCore|Wave")
    bool bLoop = true;
};