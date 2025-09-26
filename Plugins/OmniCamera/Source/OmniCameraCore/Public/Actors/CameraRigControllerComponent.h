#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// #include "InputActionValue.h"

#include "CameraRigControllerComponent.generated.h"

UCLASS()
class OMNICAMERACORE_API UCameraRigControllerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCameraRigControllerComponent(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="OmniCameraCore")
    TSubclassOf<class ACameraRig> CameraRigTemplate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OmniCameraCore")
    TObjectPtr<class UInputMappingContext> CameraDefaultInputMappingContext; 

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OmniCameraCore")
    TObjectPtr<class UInputAction> CameraZoomAction;

public:
    void BindInput(class UEnhancedInputComponent* EnhancedInputComponent);

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UFUNCTION(BlueprintCallable, Category="OmniCameraCore")
    void EnsureCameraRig();

    // Input Callbacks
    void Input_ZoomCamera(const struct FInputActionValue& Value);

private:
    UPROPERTY(Transient)
    TObjectPtr<class ACameraRig> SpawnedCameraRig;
};