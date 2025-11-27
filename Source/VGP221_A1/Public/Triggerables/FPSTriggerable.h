#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSTriggerable.generated.h"

UCLASS()
class VGP221_A1_API AFPSTriggerable : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Trigger();

	UFUNCTION(BlueprintNativeEvent, Category = "Triggerable")
	void OnTrigger();
};
