#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class VGP221_A1_API AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};
