#include "GameModes/MainMenuGameMode.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	HUDClass = AMainMenuHUD::StaticClass();
}

void AMainMenuGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);
}
