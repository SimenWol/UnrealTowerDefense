#include "Components/CameraRigControllerComponent.h"

#include "Actors/CameraRig.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Log.h"

UCameraRigControllerComponent::UCameraRigControllerComponent(const FObjectInitializer& ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UCameraRigControllerComponent::BindInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (!ensure(EnhancedInputComponent)) { return; }

    // Zoom & Rotate
    if (CameraZoomAction) { EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_ZoomCamera); }
    if (CameraRotateAction)
    {
        EnhancedInputComponent->BindAction(CameraRotateAction, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_RotateCamera);
        EnhancedInputComponent->BindAction(CameraRotateAction, ETriggerEvent::Canceled,  this, &UCameraRigControllerComponent::Input_RotateCamera);
        EnhancedInputComponent->BindAction(CameraRotateAction, ETriggerEvent::Completed, this, &UCameraRigControllerComponent::Input_RotateCamera);
    }

    // Pan (keys/joystick)
    if (CameraPanKeyXAction)      { EnhancedInputComponent->BindAction(CameraPanKeyXAction,      ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanKeyX); }
    if (CameraPanKeyYAction)      { EnhancedInputComponent->BindAction(CameraPanKeyYAction,      ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanKeyY); }
    if (CameraPanJoystickXAction) { EnhancedInputComponent->BindAction(CameraPanJoystickXAction, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanJoystickX); }
    if (CameraPanJoystickYAction) { EnhancedInputComponent->BindAction(CameraPanJoystickYAction, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanJoystickY); }
    if (CameraPanJoystickStart)
    {
        EnhancedInputComponent->BindAction(CameraPanJoystickStart, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanJoystickPressed);
        EnhancedInputComponent->BindAction(CameraPanJoystickStart, ETriggerEvent::Completed, this, &UCameraRigControllerComponent::Input_PanJoystickReleased);
        EnhancedInputComponent->BindAction(CameraPanJoystickStart, ETriggerEvent::Canceled,  this, &UCameraRigControllerComponent::Input_PanJoystickReleased);
    }
}

void UCameraRigControllerComponent::BeginPlay()
{
    Super::BeginPlay();

    EnsureCameraRig();

    if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
            {
                if (CameraDefaultInputMappingContext)
                {
                    Subsystem->AddMappingContext(CameraDefaultInputMappingContext, /* Priority */ 0);
                    UE_LOG(LogOmniCameraCore, Log, TEXT("Default Camera Mapping Context Added."));
                }
            }
        }
    }
}

void UCameraRigControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    RemovePanningMapping();

    if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
            {
                if (CameraDefaultInputMappingContext)
                {
                    Subsystem->RemoveMappingContext(CameraDefaultInputMappingContext);
                    UE_LOG(LogOmniCameraCore, Log, TEXT("Default Camera Mapping Context Removed."));
                }
            }
        }
    }

    Super::EndPlay(EndPlayReason);
}

void UCameraRigControllerComponent::EnsureCameraRig()
{
    if (SpawnedCameraRig && !SpawnedCameraRig->IsPendingKillPending()) { return; }

    APlayerController* Controller = CastChecked<APlayerController>(GetOwner());
    APawn* Pawn = Controller->GetPawn();

    if (!Pawn)
    {
        UE_LOG(LogOmniCameraCore, Warning, TEXT("No pawn possessed yet; deferring CameraRig spawn until it is."));
        return;
    }

    FVector SpawnLocation = Pawn->GetActorLocation();
    FRotator SpawnRotation = FRotator::ZeroRotator;

    if (CameraRigTemplate)
    {
        SpawnedCameraRig = GetWorld()->SpawnActor<ACameraRig>(CameraRigTemplate, SpawnLocation, SpawnRotation);
    }
    else
    {
        // If you ever place a CameraRig in level and want to re-use it:
        for (TActorIterator<ACameraRig> It(GetWorld()); It; ++It)
        {
            SpawnedCameraRig = *It;
            break;
        }
    }

    if (SpawnedCameraRig)
    {
        Controller->SetViewTarget(SpawnedCameraRig);
    }
    else
    {
        UE_LOG(LogOmniCameraCore, Warning, TEXT("Failed to create/find ACameraRig."));
    }
}

void UCameraRigControllerComponent::AddPanningMapping()
{
    if (bPanningContextActive || !CameraPanningInputMappingContext) { return; }

    if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
            {
                Subsystem->AddMappingContext(CameraPanningInputMappingContext, /* Priority */ 1);
                bPanningContextActive = true;
                UE_LOG(LogOmniCameraCore, Log, TEXT("Panning Camera Mapping Context Added."));
            }
        }
    }
}

void UCameraRigControllerComponent::RemovePanningMapping()
{
    if (!bPanningContextActive || !CameraPanningInputMappingContext) { return; }

    if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
            {
                Subsystem->RemoveMappingContext(CameraPanningInputMappingContext);
                bPanningContextActive = false;
                UE_LOG(LogOmniCameraCore, Log, TEXT("Panning Camera Mapping Context Removed."));
            }
        }
    }
}

void UCameraRigControllerComponent::Input_RotateCamera(const FInputActionValue& Value)
{
    if (SpawnedCameraRig) { SpawnedCameraRig->AddRotationInput(Value.Get<float>()); }
}

void UCameraRigControllerComponent::Input_ZoomCamera(const struct FInputActionValue& Value)
{
    if (SpawnedCameraRig) { SpawnedCameraRig->AddZoomInput(Value.Get<float>()); }
}

void UCameraRigControllerComponent::Input_PanKeyX(const struct FInputActionValue& Value)
{
    if (SpawnedCameraRig) { SpawnedCameraRig->AddPanKeyXInput(Value.Get<float>()); }
}

void UCameraRigControllerComponent::Input_PanKeyY(const struct FInputActionValue& Value)
{
    if (SpawnedCameraRig) { SpawnedCameraRig->AddPanKeyYInput(Value.Get<float>()); }
}

void UCameraRigControllerComponent::Input_PanJoystickX(const struct FInputActionValue& Value)
{
    if (SpawnedCameraRig) { SpawnedCameraRig->AddPanJoystickXInput(Value.Get<float>()); }
}

void UCameraRigControllerComponent::Input_PanJoystickY(const struct FInputActionValue& Value)
{
    if (SpawnedCameraRig) { SpawnedCameraRig->AddPanJoystickYInput(Value.Get<float>()); }
}

void UCameraRigControllerComponent::Input_PanJoystickPressed(const struct FInputActionValue& Value)
{
    if (Value.Get<bool>() && SpawnedCameraRig)
    {
        SpawnedCameraRig->StartJoystickPan();
        AddPanningMapping();
    }
}

void UCameraRigControllerComponent::Input_PanJoystickReleased(const struct FInputActionValue& Value)
{
    if (!Value.Get<bool>() && SpawnedCameraRig)
    {
        SpawnedCameraRig->EndJoystickPan();
        RemovePanningMapping();
    }
}