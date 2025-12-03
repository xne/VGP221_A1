#include "GUI/FPSHUD.h"

void AFPSHUD::BeginPlay()
{
	Super::BeginPlay();

	PushGameMenu(FirstGameMenuClass);
}

void AFPSHUD::PushGameMenu(TSubclassOf<UGameMenuWidget> GameMenuClass)
{
	GameMenuWidget = CreateWidget<UGameMenuWidget>(GetWorld(), GameMenuClass);
	GameMenuWidget->AddToViewport();
}

void AFPSHUD::PopGameMenu()
{
	if (GameMenuWidget)
	{
		GameMenuWidget->RemoveFromParent();
		GameMenuWidget = nullptr;
	}
}
