#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TDPlayerController.generated.h"

UCLASS()
class ATDPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ATDPlayerController(const FObjectInitializer& ObjectInitializer);
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    TObjectPtr<class UCameraRigControllerComponent> CameraRigControllerComponent;
};