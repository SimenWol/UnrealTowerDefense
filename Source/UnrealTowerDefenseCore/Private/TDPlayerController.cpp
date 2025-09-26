#include "TDPlayerController.h"

#include "Actors/CameraRigControllerComponent.h"

ATDPlayerController::ATDPlayerController(const FObjectInitializer& ObjectInitializer)
{
    CameraRigControllerComponent = CreateDefaultSubobject<UCameraRigControllerComponent>(TEXT("CameraRigControllerComponent"));
}