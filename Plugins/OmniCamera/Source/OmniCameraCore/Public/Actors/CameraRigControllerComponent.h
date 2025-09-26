#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CameraRigControllerComponent.generated.h"

UCLASS()
class OMNICAMERACORE_API UCameraRigControllerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCameraRigControllerComponent(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="OmniCameraCore")
    TSubclassOf<class ACameraRig> CameraRigTemplate;

    virtual void BeginPlay() override;
    // virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UFUNCTION(BlueprintCallable, Category="OmniCameraCore")
    void EnsureCameraRig();

private:
    UPROPERTY(Transient)
    TObjectPtr<class ACameraRig> SpawnedCameraRig;
};