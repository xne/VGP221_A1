#include "GUI/GameHUD.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	PushMenu(GameMenuClass);
}
