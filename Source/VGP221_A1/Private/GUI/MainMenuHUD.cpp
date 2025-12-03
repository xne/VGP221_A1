#include "GUI/MainMenuHUD.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	auto GameInstance = GetGameInstance<UFPSGameInstance>();
	if (GameInstance->bGameOver)
	{
		GameInstance->bGameOver = false;

		if (GameOverClass)
			PushMenu(GameOverClass);
	}
	else if (MainMenuClass)
		PushMenu(MainMenuClass);
}
