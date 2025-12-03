#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPSGameInstance.generated.h"

UCLASS()
class VGP221_A1_API UFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	bool bGameOver = false;
};
