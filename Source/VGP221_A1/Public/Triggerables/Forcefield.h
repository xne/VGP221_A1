#pragma once

#include "CoreMinimal.h"
#include "Triggerables/FPSTriggerable.h"
#include "Forcefield.generated.h"

UCLASS()
class VGP221_A1_API AForcefield : public AFPSTriggerable
{
	GENERATED_BODY()

public:
	AForcefield();

	UPROPERTY(VisibleDefaultsOnly, Category = "Forcefield")
	UStaticMeshComponent* ForcefieldMeshComponent;

	virtual void OnTrigger_Implementation() override;
};
