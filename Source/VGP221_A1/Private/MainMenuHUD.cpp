#include "MainMenuHUD.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	PushMainMenu(FirstMainMenuClass);
}

void AMainMenuHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AMainMenuHUD::PushMainMenu(TSubclassOf<UMainMenuWidget> MainMenuClass)
{
	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuClass);
	MainMenuWidget->AddToViewport();
}

void AMainMenuHUD::PopMainMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}
}
