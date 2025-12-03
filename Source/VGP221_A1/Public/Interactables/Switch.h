#pragma once

#include "CoreMinimal.h"
#include "Interactables/FPSInteractable.h"
#include "Triggerables/FPSTriggerable.h"
#include "Switch.generated.h"

UCLASS()
class VGP221_A1_API ASwitch : public AFPSInteractable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly)
	AFPSTriggerable* Triggerable;

	virtual void OnInteract_Implementation() override;
};
