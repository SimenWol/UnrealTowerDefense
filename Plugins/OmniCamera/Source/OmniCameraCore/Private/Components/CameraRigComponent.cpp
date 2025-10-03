#include "Components/CameraRigComponent.h"
#include "Actors/CameraRig.h"
#include "Log.h"

UCameraRigComponent::UCameraRigComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCameraRigComponent::BeginPlay()
{
    Super::BeginPlay();

    CameraRig = Cast<ACameraRig>(GetOwner());
    if (!CameraRig)
    {
        UE_LOG(LogOmniCameraCore, Log, TEXT("Unable to retrieve the Owner Class as a ACameraRig"));
    }
}