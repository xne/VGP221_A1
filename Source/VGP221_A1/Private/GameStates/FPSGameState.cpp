#include "GameStates/FPSGameState.h"

void AFPSGameState::RegisterTask()
{
	Tasks++;
}

void AFPSGameState::CompleteTask()
{
	TasksComplete++;

	if (TasksComplete == Tasks)
	{
		auto GameInstance = GetGameInstance<UFPSGameInstance>();
		if (GameInstance)
			GameInstance->bGameOver = true;

		UGameplayStatics::OpenLevel(this, Levels::Menu);
	}
}
