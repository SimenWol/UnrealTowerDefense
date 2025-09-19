#include "TDGameMode.h"

#include "TDPawn.h"
#include "TDPlayerController.h"
#include "TDHUD.h"
#include "TDPlayerState.h"
#include "TDGameState.h"

ATDGameMode::ATDGameMode(const FObjectInitializer& ObjectInitializer)
{
    DefaultPawnClass = ATDPawn::StaticClass();
    PlayerControllerClass = ATDPlayerController::StaticClass();
    HUDClass = ATDHUD::StaticClass();
    PlayerStateClass = ATDPlayerState::StaticClass();
    GameStateClass = ATDGameState::StaticClass();
}