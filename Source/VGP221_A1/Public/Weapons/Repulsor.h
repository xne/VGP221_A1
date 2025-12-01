#pragma once

#include "CoreMinimal.h"
#include "Engine/OverlapResult.h"
#include "Weapons/FPSWeapon.h"
#include "Repulsor.generated.h"

UCLASS()
class VGP221_A1_API ARepulsor : public AFPSWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Repulsor")
	float Range = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Repulsor")
	float Strength = 100.f;

	virtual void OnFire_Implementation() override;
};
