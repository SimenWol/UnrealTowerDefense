#include "TDPlayerController.h"

#include "Actors/CameraRigControllerComponent.h"
#include "EnhancedInputComponent.h"

ATDPlayerController::ATDPlayerController(const FObjectInitializer& ObjectInitializer)
{
    CameraRigControllerComponent = CreateDefaultSubobject<UCameraRigControllerComponent>(TEXT("CameraRigControllerComponent"));
}

void ATDPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (CameraRigControllerComponent)
    {
        UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
        if (ensureMsgf(EnhancedInputComponent, TEXT("InputComponent is not an EnhancedInputComponent")))
        {
            CameraRigControllerComponent->BindInput(EnhancedInputComponent);
        }
    }
}