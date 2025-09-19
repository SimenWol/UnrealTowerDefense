#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CameraRig.generated.h"

UCLASS()
class ACameraRig : public AActor
{
    GENERATED_BODY()

public:
    ACameraRig(const FObjectInitializer& ObjectInitializer);

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="OmniCameraCore")
    TObjectPtr<class USpringArmComponent> SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="OmniCameraCore")
    TObjectPtr<class UCameraComponent> Camera;
};