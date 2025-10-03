#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CameraRig.generated.h"

UCLASS()
class OMNICAMERACORE_API ACameraRig : public AActor
{
    GENERATED_BODY()

public:
    ACameraRig(const FObjectInitializer& ObjectInitializer);

public:
    UPROPERTY(VisibleAnywhere, Category="OmniCameraCore")
    TObjectPtr<class USpringArmComponent> SpringArm;

    UPROPERTY(VisibleAnywhere, Category="OmniCameraCore")
    TObjectPtr<class UCameraComponent> Camera;

    UPROPERTY(VisibleAnywhere, Category="OmniCameraCore")
    TObjectPtr<class UCameraRigZoomComponent> CameraZoom;
    UPROPERTY(VisibleAnywhere, Category="OmniCameraCore")
    TObjectPtr<class UCameraRigPanComponent> CameraPan;
    UPROPERTY(VisibleAnywhere, Category="OmniCameraCore")
    TObjectPtr<class UCameraRigRotateComponent> CameraRotate;

public:
    void AddRotationInput(float Value);
    void AddZoomInput(float Value);
    void AddPanKeyXInput(float Value);
    void AddPanKeyYInput(float Value);

    void AddPanJoystickXInput(float Value);
    void AddPanJoystickYInput(float Value);
    void StartJoystickPan();
    void EndJoystickPan();
};