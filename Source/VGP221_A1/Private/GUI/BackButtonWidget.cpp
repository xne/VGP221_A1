#include "GUI/BackButtonWidget.h"

void UBackButtonWidget::OnClick_Implementation()
{
	auto MainMenuHUD = GetOwningPlayer()->GetHUD<AMainMenuHUD>();;

	if (MainMenuHUD)
	{
		MainMenuHUD->PopMainMenu();
		MainMenuHUD->PushMainMenu(LastMainMenuClass);
	}
}
