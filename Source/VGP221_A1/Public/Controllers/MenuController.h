#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

UCLASS()
class VGP221_A1_API AMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
};
