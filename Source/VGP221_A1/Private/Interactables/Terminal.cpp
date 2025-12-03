#include "Interactables/Terminal.h"

void ATerminal::BeginPlay()
{
	auto GameState = GetWorld()->GetGameState<AFPSGameState>();
	if (GameState)
		GameState->RegisterTask();
}

void ATerminal::OnInteract_Implementation()
{
	if (bActive)
		return;
	bActive = true;

	if (InteractableMeshComponent && ActiveMaterial)
		InteractableMeshComponent->SetMaterial(ActiveMaterialIdx, ActiveMaterial);

	auto GameState = GetWorld()->GetGameState<AFPSGameState>();
	if (GameState)
		GameState->CompleteTask();
}
