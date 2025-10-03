#include "Components/CameraRigZoomComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/CameraRig.h"

UCameraRigZoomComponent::UCameraRigZoomComponent()
{
    ZoomSpeed = 200.0f;
    MinArmLength = 300.0f;
    MaxArmLength = 1500.0f;
}

void UCameraRigZoomComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Nothing to implement
}

void UCameraRigZoomComponent::OnZoomCamera(float Value)
{
    if (CameraRig == nullptr)
    {
        return;
    }

    if (FMath::IsNearlyZero(Value))
    {
        return;
    }
    
    float Desired = CameraRig->SpringArm->TargetArmLength - (Value * ZoomSpeed);
    Desired = FMath::Clamp(Desired, MinArmLength, MaxArmLength);
    CameraRig->SpringArm->TargetArmLength = Desired;
}