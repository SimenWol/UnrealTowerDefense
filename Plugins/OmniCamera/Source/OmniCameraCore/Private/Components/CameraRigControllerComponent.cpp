#include "Components/CameraRigControllerComponent.h"

#include "Actors/CameraRig.h"
#include "Components/CameraRigZoomComponent.h"
#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Log.h"

UCameraRigControllerComponent::UCameraRigControllerComponent(const FObjectInitializer& ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCameraRigControllerComponent::BindInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (ensure(EnhancedInputComponent))
    {
        if (CameraZoomAction)
        {
            EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_ZoomCamera);
        }
    }
}

void UCameraRigControllerComponent::BeginPlay()
{
    Super::BeginPlay();

    EnsureCameraRig();

    if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            if (CameraDefaultInputMappingContext)
            {
                Subsystem->AddMappingContext(CameraDefaultInputMappingContext, 0);
            }
        }
    }
}

void UCameraRigControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            if (CameraDefaultInputMappingContext)
            {
                Subsystem->RemoveMappingContext(CameraDefaultInputMappingContext);
            }
        }
    }
}

void UCameraRigControllerComponent::EnsureCameraRig()
{
    //if we already have a valid CameraRigActor:
    //    return
    if (SpawnedCameraRig && !SpawnedCameraRig->IsPendingKillPending())
    {
        return;
    }

    //controller = get owner as PlayerController
    //pawn = controller.getPawn()
    APlayerController* Controller = CastChecked<APlayerController>(GetOwner());
    APawn* Pawn = Controller->GetPawn();

    //if pawn is not valid:
    //    log warning "No Pawn possessed yet; wait until later"
    //    return
    if (!Pawn)
    {
        UE_LOG(LogOmniCameraCore, Warning, TEXT("No pawn possessed yet; wait until later"));
        return;
    }

    //spawnLocation = pawn.position
    //spawnRotation = zeroRotation
    FVector SpawnLocation = Pawn->GetActorLocation();
    FRotator SpawnRotation = FRotator::ZeroRotator;

    //if we have a CameraRigTemplate:
    //    CameraRigActor = spawn new CameraRig from template at spawnLocation with spawnRotation
    //else:
    //    CameraRigActor = find any existing CameraRig in the world
    if (CameraRigTemplate)
    {
        SpawnedCameraRig = GetWorld()->SpawnActor<ACameraRig>(CameraRigTemplate, SpawnLocation, SpawnRotation);
    }
    else
    {
        for (TActorIterator<ACameraRig> It(GetWorld()); It; ++It)
        {
            SpawnedCameraRig = *It;
            break;
        }
    }

    //if CameraRigActor is valid:
    //    set viewtarget for controller using CameraRig
    //else:
    //    log warning "Could not create or find a CameraRig"
    if (SpawnedCameraRig)
    {
        Controller->SetViewTarget(SpawnedCameraRig);
    }
    else
    {
        UE_LOG(LogOmniCameraCore, Warning, TEXT("Could not create or find a CameraRig"));
        return;
    }
}

void UCameraRigControllerComponent::Input_ZoomCamera(const struct FInputActionValue& Value)
{
    if (SpawnedCameraRig)
    {
        SpawnedCameraRig->CameraZoom->OnZoomCamera(Value.Get<float>());
    }
}