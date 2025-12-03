#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

UCLASS()
class VGP221_A1_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
};
