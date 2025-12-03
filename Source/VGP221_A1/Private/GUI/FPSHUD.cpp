#include "GUI/FPSHUD.h"

void AFPSHUD::PushMenu(TSubclassOf<UMenuWidget> GameMenuClass)
{
	MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), GameMenuClass);
	MenuWidget->AddToViewport();
}

void AFPSHUD::PopMenu()
{
	if (MenuWidget)
	{
		MenuWidget->RemoveFromParent();
		MenuWidget = nullptr;
	}
}
