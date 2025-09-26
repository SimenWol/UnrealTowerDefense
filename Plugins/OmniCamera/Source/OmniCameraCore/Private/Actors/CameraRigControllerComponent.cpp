#include "Actors/CameraRigControllerComponent.h"

#include "Actors/CameraRig.h"
#include "EngineUtils.h"
#include "Log.h"
#include "GameFramework/PlayerController.h"

UCameraRigControllerComponent::UCameraRigControllerComponent(const FObjectInitializer& ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCameraRigControllerComponent::BeginPlay()
{
    Super::BeginPlay();

    EnsureCameraRig();
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