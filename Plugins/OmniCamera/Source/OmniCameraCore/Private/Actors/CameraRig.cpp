#include "Actors/CameraRig.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACameraRig::ACameraRig(const FObjectInitializer& ObjectInitializer)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->SetRelativeLocation({-250.0f, 0.0f, 0.0f});
    SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
    SpringArm->TargetArmLength = 1000.0f;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}