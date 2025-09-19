#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "TDGameMode.generated.h"

UCLASS()
class ATDGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATDGameMode(const FObjectInitializer& ObjectInitializer);
};