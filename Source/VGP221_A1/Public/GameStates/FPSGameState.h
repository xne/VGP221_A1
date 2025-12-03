#pragma once

#include "CoreMinimal.h"
#include "FPSGameInstance.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Paths.h"
#include "FPSGameState.generated.h"

UCLASS()
class VGP221_A1_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterTask();

	UFUNCTION(BlueprintCallable)
	void CompleteTask();

private:
	int Tasks;
	int TasksComplete;
};
