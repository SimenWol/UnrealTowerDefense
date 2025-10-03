#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"

#include "CameraRigControllerComponent.generated.h"

class ACameraRig;
class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;

/**
 * Attach to a PlayerController to guarantee a CameraRig exists and bind camera input.
 */
UCLASS(BlueprintType, ClassGroup=(Input), meta=(BlueprintSpawnableComponent))
class OMNICAMERACORE_API UCameraRigControllerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCameraRigControllerComponent(const FObjectInitializer& ObjectInitializer);
    
    /** Call from the owning PlayerController's SetupInputComponent. */
    void BindInput(class UEnhancedInputComponent* EnhancedInputComponent);

public:
    /** Template to spawn if no CameraRig exists. */
    UPROPERTY(EditDefaultsOnly, Category="OmniCameraCore|Input")
    TSubclassOf<ACameraRig> CameraRigTemplate;

    /** Mapping added at BeginPlay (your default mapping stays on the controller). */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OmniCameraCore|Input")
    TObjectPtr<UInputMappingContext> CameraDefaultInputMappingContext = nullptr; 

    /** Mapping toggled when joystick panning is active. */
    UPROPERTY(EditDefaultsOnly, Category="OmniCameraCore|Input")
    TObjectPtr<UInputMappingContext> CameraPanningInputMappingContext = nullptr;

    // Actions
    UPROPERTY(EditDefaultsOnly, Category="OmniCameraCore|Input")
    TObjectPtr<UInputAction> CameraZoomAction = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="OmniCameraCore|Input")
    TObjectPtr<UInputAction> CameraRotateAction = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="OmniCameraCore|Input")
    TObjectPtr<UInputAction> CameraPanKeyXAction = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="OmniCameraCore|Input")
    TObjectPtr<UInputAction> CameraPanKeyYAction = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="OmniCameraCore|Input")
    TObjectPtr<UInputAction> CameraPanJoystickXAction = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="OmniCameraCore|Input")
    TObjectPtr<UInputAction> CameraPanJoystickYAction = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="OmniCameraCore|Input")
    TObjectPtr<UInputAction> CameraPanJoystickStart = nullptr;

private:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // Helpers
    void EnsureCameraRig();
    void AddPanningMapping();
    void RemovePanningMapping();

    // Input Callbacks
    void Input_RotateCamera(const struct FInputActionValue& Value);
    void Input_ZoomCamera(const struct FInputActionValue& Value);
    void Input_PanKeyX(const struct FInputActionValue& Value);
    void Input_PanKeyY(const struct FInputActionValue& Value);
    void Input_PanJoystickX(const struct FInputActionValue& Value);
    void Input_PanJoystickY(const struct FInputActionValue& Value);
    void Input_PanJoystickPressed(const struct FInputActionValue& Value);
    void Input_PanJoystickReleased(const struct FInputActionValue& Value);

private:
    UPROPERTY()
    TObjectPtr<class ACameraRig> SpawnedCameraRig;

    bool bPanningContextActive = false;
};