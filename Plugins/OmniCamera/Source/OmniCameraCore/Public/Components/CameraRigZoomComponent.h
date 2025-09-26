#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CameraRigZoomComponent.generated.h"

UCLASS()
class UCameraRigZoomComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCameraRigZoomComponent(const FObjectInitializer& ObjectInitializer);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OmniCameraCore")
    float ZoomSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OmniCameraCore")
    float MinArmLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OmniCameraCore")
    float MaxArmLength;

public:
    void BeginPlay() override;
    void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    void OnZoomCamera(float Value);

private:
    UPROPERTY(VisibleAnywhere, Category="OmniCameraCore")
    TObjectPtr<class ACameraRig> CameraRig;
};