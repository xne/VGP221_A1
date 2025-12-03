#include "GUI/MainMenuHUD.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	auto GameInstance = GetGameInstance<UFPSGameInstance>();
	if (GameInstance)
	{
		if (GameInstance->bGameOver)
		{
			GameInstance->bGameOver = false;

			if (GameOverClass)
				PushMenu(GameOverClass);

			return;
		}
	}
	
	if (MainMenuClass)
		PushMenu(MainMenuClass);
}
