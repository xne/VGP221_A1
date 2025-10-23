#include "FPSGameMode.h"

void AFPSGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);
}
