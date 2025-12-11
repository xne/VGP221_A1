#include "GUI/GameMenuWidget.h"

void UGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateHealthBar(1.f);
	UpdateTimeText(90);
	UpdateTasksText(0, 1);

	auto GameState = GetWorld()->GetGameState<AFPSGameState>();
	if (GameState)
	{
		GameState->OnTaskRegister.AddDynamic(this, &UGameMenuWidget::OnGameStateTaskRegister);
		GameState->OnTaskComplete.AddDynamic(this, &UGameMenuWidget::OnGameStateTaskComplete);
	}
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

void UGameMenuWidget::UpdateTasksText(int Tasks, int TasksComplete)
{
	if (!TasksText)
		return;

	TasksText->SetText(FText::FromString(FString::Printf(TEXT("Tasks: %d/%d"), TasksComplete, Tasks)));
}

void UGameMenuWidget::OnGameStateTaskRegister()
{
	auto GameState = GetWorld()->GetGameState<AFPSGameState>();
	if (GameState)
		UpdateTasksText(GameState->GetTasks(), GameState->GetTasksComplete());
}

void UGameMenuWidget::OnGameStateTaskComplete()
{
	auto GameState = GetWorld()->GetGameState<AFPSGameState>();
	if (GameState)
		UpdateTasksText(GameState->GetTasks(), GameState->GetTasksComplete());
}
