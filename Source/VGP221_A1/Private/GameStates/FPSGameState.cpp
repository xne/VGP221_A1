#include "GameStates/FPSGameState.h"

void AFPSGameState::RegisterTask()
{
	Tasks++;
}

void AFPSGameState::CompleteTask()
{
	TasksComplete++;

	OnTaskComplete.Broadcast();
}

int AFPSGameState::GetTasks() const
{
	return Tasks;
}

int AFPSGameState::GetTasksComplete() const
{
	return TasksComplete;
}
