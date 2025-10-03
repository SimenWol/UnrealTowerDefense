#pragma once

#include "CoreMinimal.h"
#include "Components/CameraRigComponent.h"

#include "CameraRigRotateComponent.generated.h"

UCLASS()
class OMNICAMERACORE_API UCameraRigRotateComponent : public UCameraRigComponent
{
    GENERATED_BODY()

public:
    UCameraRigRotateComponent();

public:
    UPROPERTY(EditAnywhere, Category="OmniCameraCore")
    float RotationSpeed;

public:
    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

    void SetCurrentRotationInput(float Value) { CurrentRotationInput = Value; }

    float GetCurrentRotationInput() const { return CurrentRotationInput; }

public:
    void OnRotateCamera(float Value);

private:
    float CurrentRotationInput;
};