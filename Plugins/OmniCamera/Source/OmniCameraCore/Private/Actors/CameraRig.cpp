#include "Actors/CameraRig.h"

#include "Components/CameraRigPanComponent.h"
#include "Components/CameraRigZoomComponent.h"
#include "Components/CameraRigRotateComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Kismet/GameplayStatics.h"

ACameraRig::ACameraRig(const FObjectInitializer& ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->SetRelativeLocation({-250.0f, 0.0f, 0.0f});
    SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
    SpringArm->TargetArmLength = 1000.0f;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    CameraZoom = CreateDefaultSubobject<UCameraRigZoomComponent>(TEXT("Camera Zoom"));
    CameraPan = CreateDefaultSubobject<UCameraRigPanComponent>(TEXT("Camera Pan"));
    CameraRotate = CreateDefaultSubobject<UCameraRigRotateComponent>(TEXT("Camera Rotate"));
}

void ACameraRig::AddRotationInput(float Value)
{
    if (CameraRotate)
    {
        CameraRotate->OnRotateCamera(Value);
    }
}

void ACameraRig::AddZoomInput(float Value)
{
    if (CameraZoom)
    {
        CameraZoom->OnZoomCamera(Value);
    }
}

void ACameraRig::AddPanKeyXInput(float Value)
{
    if (CameraPan)
    {
        CameraPan->OnPanKeyX(Value);
    }
}

void ACameraRig::AddPanKeyYInput(float Value)
{
    if (CameraPan)
    {
        CameraPan->OnPanKeyY(Value);
    }
}

void ACameraRig::AddPanJoystickXInput(float Value)
{
    if (CameraPan)
    {
        CameraPan->OnPanJoystickX(Value);
    }
}

void ACameraRig::AddPanJoystickYInput(float Value)
{
    if (CameraPan)
    {
        CameraPan->OnPanJoystickY(Value);
    }
}

void ACameraRig::StartJoystickPan()
{
    if (CameraPan)
    {
        CameraPan->OnPanJoystickPressed();
    }
}

void ACameraRig::EndJoystickPan()
{
    if (CameraPan)
    {
        CameraPan->OnPanJoystickReleased();
    }
}