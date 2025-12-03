#include "GameModes/FPSGameMode.h"

AFPSGameMode::AFPSGameMode()
{
	GameStateClass = AFPSGameState::StaticClass();
	HUDClass = AFPSHUD::StaticClass();
	DefaultPawnClass = AFPSCharacter::StaticClass();
}

void AFPSGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);
}
