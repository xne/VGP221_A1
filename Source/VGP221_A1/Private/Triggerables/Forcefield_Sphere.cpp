#include "Triggerables/Forcefield_Sphere.h"

void AForcefield_Sphere::BeginPlay()
{
	Super::BeginPlay();

	auto GameState = GetWorld()->GetGameState<AFPSGameState>();
	if (GameState)
		GameState->OnTaskComplete.AddDynamic(this, &AForcefield_Sphere::OnGameStateTaskComplete);
}

void AForcefield_Sphere::OnGameStateTaskComplete()
{
	auto GameState = GetWorld()->GetGameState<AFPSGameState>();
	if (GameState)
	{
		if (GameState->GetTasksComplete() == GameState->GetTasks())
			FadeOut();
	}
}
