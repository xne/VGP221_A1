#include "GUI/GameMenuWidget.h"

void UGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateHealthBar(1.f);
}

void UGameMenuWidget::UpdateHealthBar(float HealthPercent)
{
	if (!HealthBar)
		return;

	HealthBar->SetPercent(HealthPercent);
}
