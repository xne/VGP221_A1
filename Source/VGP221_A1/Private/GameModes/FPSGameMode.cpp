#include "GameModes/FPSGameMode.h"

AFPSGameMode::AFPSGameMode()
{
	HUDClass = AFPSHUD::StaticClass();
	DefaultPawnClass = AFPSCharacter::StaticClass();
}

void AFPSGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);
}
