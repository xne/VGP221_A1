#include "GUI/SetMenuButtonWidget.h"

void USetMenuButtonWidget::OnClick_Implementation()
{
	auto HUD = GetOwningPlayer()->GetHUD<AFPSHUD>();;

	if (HUD)
	{
		HUD->PopMenu();
		HUD->PushMenu(MenuClass);
	}
}
