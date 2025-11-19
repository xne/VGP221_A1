#include "GUI/GameMenuWidget.h"

void UGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateHealthBar(1.f);
	UpdateTimeText(90.f);
	UpdateScoreText(0.f);
}

void UGameMenuWidget::UpdateHealthBar(float HealthPercent)
{
	if (!HealthBar)
		return;

	HealthBar->SetPercent(HealthPercent);
}

void UGameMenuWidget::UpdateTimeText(int Time)
{
	if (!TimeText)
		return;

	TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.2d:%.2d"), Time / 60, Time % 60)));
}

void UGameMenuWidget::UpdateScoreText(int Score)
{
	if (!ScoreText)
		return;

	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %.4d"), Score)));
}
