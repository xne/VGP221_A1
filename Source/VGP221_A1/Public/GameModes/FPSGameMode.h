#pragma once

#include "CoreMinimal.h"
#include "Characters/FPSCharacter.h"
#include "GUI/FPSHUD.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class VGP221_A1_API AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSGameMode();

protected:
	virtual void StartPlay() override;
};
