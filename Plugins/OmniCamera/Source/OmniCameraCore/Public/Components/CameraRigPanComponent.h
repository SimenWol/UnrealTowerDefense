#pragma once

#include "CoreMinimal.h"
#include "Components/CameraRigComponent.h"

#include "CameraRigPanComponent.generated.h"

UCLASS()
class OMNICAMERACORE_API UCameraRigPanComponent : public UCameraRigComponent
{
    GENERATED_BODY()

public:
    UCameraRigPanComponent();

public:
    UPROPERTY(EditAnywhere, Category="OmniCameraCore")
    float PanSpeed;
    UPROPERTY(EditAnywhere, Category="OmniCameraCore")
    float MinX;
    UPROPERTY(EditAnywhere, Category="OmniCameraCore")
    float MaxX;
    UPROPERTY(EditAnywhere, Category="OmniCameraCore")
    float MinY;
    UPROPERTY(EditAnywhere, Category="OmniCameraCore")
    float MaxY;
    
public:
    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

    void SetJoystickPanning(bool bIsPanning) { bIsJoyStickPanning = bIsPanning; }
    void SetPanInputX(float Value) { PanInputX = Value; }
    void SetPanInputY(float Value) { PanInputY = Value; }

    bool IsJoyStickPanning() const { return bIsJoyStickPanning; }
    float GetPanInputX() const { return PanInputX; }
    float GetPanInputY() const { return PanInputY; }

public:
    void OnPanJoystickX(float Value);
    void OnPanJoystickY(float Value);
    void OnPanJoystickPressed();
    void OnPanJoystickReleased();
    void OnPanKeyX(float Value);
    void OnPanKeyY(float Value);

private:
    bool bIsJoyStickPanning;

    float PanInputX;
    float PanInputY;
};