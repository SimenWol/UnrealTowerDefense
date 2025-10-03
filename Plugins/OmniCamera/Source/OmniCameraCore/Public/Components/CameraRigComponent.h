#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraRigComponent.generated.h"

UCLASS()
class OMNICAMERACORE_API UCameraRigComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCameraRigComponent();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="OmniCameraCore")
    TObjectPtr<class ACameraRig> CameraRig;

protected:
    void BeginPlay() override;
};