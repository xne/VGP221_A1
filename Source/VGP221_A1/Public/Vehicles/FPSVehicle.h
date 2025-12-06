#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSVehicle.generated.h"

UCLASS()
class VGP221_A1_API AFPSVehicle : public APawn
{
	GENERATED_BODY()

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
