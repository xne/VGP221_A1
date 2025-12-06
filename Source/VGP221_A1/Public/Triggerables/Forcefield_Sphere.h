#pragma once

#include "CoreMinimal.h"
#include "GameStates/FPSGameState.h"
#include "Triggerables/Forcefield.h"
#include "Forcefield_Sphere.generated.h"

UCLASS()
class VGP221_A1_API AForcefield_Sphere : public AForcefield
{
	GENERATED_BODY()

public:
	AForcefield_Sphere();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnGameStateTaskComplete();
};
