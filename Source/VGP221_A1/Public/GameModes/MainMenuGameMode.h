#pragma once

#include "CoreMinimal.h"
#include "GUI/MainMenuHUD.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class VGP221_A1_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainMenuGameMode();

protected:
	virtual void StartPlay() override;
};
