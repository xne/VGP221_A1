#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTaskRegister);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTaskComplete);

UCLASS()
class VGP221_A1_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	FOnTaskRegister OnTaskRegister;
	FOnTaskComplete OnTaskComplete;

	UFUNCTION(BlueprintCallable)
	void RegisterTask();

	UFUNCTION(BlueprintCallable)
	void CompleteTask();

	UFUNCTION(BlueprintPure)
	int GetTasks() const;

	UFUNCTION(BlueprintPure)
	int GetTasksComplete() const;

private:
	int Tasks;
	int TasksComplete;
};
