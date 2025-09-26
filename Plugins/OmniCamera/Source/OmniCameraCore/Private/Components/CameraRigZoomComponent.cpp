#include "Components/CameraRigZoomComponent.h"
#include "Actors/CameraRig.h"
#include "GameFramework/SpringArmComponent.h"
#include "Log.h"

UCameraRigZoomComponent::UCameraRigZoomComponent(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;

    ZoomSpeed = 200.0f;
    MinArmLength = 300.0f;
    MaxArmLength = 1500.0f;
}

void UCameraRigZoomComponent::BeginPlay()
{
    Super::BeginPlay();

    CameraRig = Cast<ACameraRig>(GetOwner());

    if (!CameraRig)
    {
        UE_LOG(LogOmniCameraCore, Log, TEXT("Owner is not a CameraRig!"));
    }
}

void UCameraRigZoomComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Nothing to implement yet
}

void UCameraRigZoomComponent::OnZoomCamera(float Value)
{
    if (CameraRig && /*Ensure(*/CameraRig->SpringArm)
    {
        if (FMath::IsNearlyZero(Value))
        {
            return;
        }

        float Desired = CameraRig->SpringArm->TargetArmLength - (Value * ZoomSpeed * GetWorld()->GetDeltaSeconds());
        Desired = FMath::Clamp(Desired, MinArmLength, MaxArmLength);
        CameraRig->SpringArm->TargetArmLength = Desired;
    }
}