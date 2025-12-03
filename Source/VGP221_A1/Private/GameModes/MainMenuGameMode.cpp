#include "GameModes/MainMenuGameMode.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	HUDClass = AMainMenuHUD::StaticClass();
	PlayerControllerClass = AMenuController::StaticClass();
}

void AMainMenuGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);
}
