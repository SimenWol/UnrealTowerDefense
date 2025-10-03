#include "Components/CameraRigPanComponent.h"

UCameraRigPanComponent::UCameraRigPanComponent()
{
    PanSpeed = 1000.0f;
    MinX = -2500.0f;
    MaxX = 2500.0f;
    MinY = -2500.0f;
    MaxY = 2500.0f;
    bIsJoyStickPanning = false;
    PanInputX = 0.0f;
    PanInputY = 0.0f;
}

void UCameraRigPanComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsJoyStickPanning)
    {
        FVector Right = GetOwner()->GetActorRightVector();
        FVector Forward = GetOwner()->GetActorForwardVector();

        FVector DeltaLocation = (Right * -PanInputX + Forward * -PanInputY) * PanSpeed * DeltaTime;
        FVector NewLocation = GetOwner()->GetActorLocation() + DeltaLocation;
        NewLocation.X = FMath::Clamp(NewLocation.X, MinX, MaxX);
        NewLocation.Y = FMath::Clamp(NewLocation.Y, MinY, MaxY);
        GetOwner()->SetActorLocation(NewLocation);

        PanInputX = 0.0f;
        PanInputY = 0.0f;
    }
}

void UCameraRigPanComponent::OnPanJoystickX(float Value)
{
    PanInputX = Value;
}

void UCameraRigPanComponent::OnPanJoystickY(float Value)
{
    PanInputY = Value;
}

void UCameraRigPanComponent::OnPanKeyX(float Value)
{
    FVector Right = GetOwner()->GetActorRightVector();
    
    FVector DeltaLocation = (Right * -Value) * PanSpeed * GetWorld()->GetDeltaSeconds();
    FVector NewLocation = GetOwner()->GetActorLocation() + DeltaLocation;
    NewLocation.X = FMath::Clamp(NewLocation.X, MinX, MaxX);
    GetOwner()->SetActorLocation(NewLocation);
}

void UCameraRigPanComponent::OnPanKeyY(float Value)
{
    FVector Forward = GetOwner()->GetActorForwardVector();
    
    FVector DeltaLocation = (Forward * -Value) * PanSpeed * GetWorld()->GetDeltaSeconds();
    FVector NewLocation = GetOwner()->GetActorLocation() + DeltaLocation;
    NewLocation.X = FMath::Clamp(NewLocation.Y, MinY, MaxY);
    GetOwner()->SetActorLocation(NewLocation);
}

void UCameraRigPanComponent::OnPanJoystickPressed()
{
    bIsJoyStickPanning = true;
}

void UCameraRigPanComponent::OnPanJoystickReleased()
{
    bIsJoyStickPanning = false;
}