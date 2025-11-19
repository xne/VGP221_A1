#include "GUI/QuitButtonWidget.h"

void UQuitButtonWidget::OnClick_Implementation()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
