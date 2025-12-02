#pragma once

#include "CoreMinimal.h"
#include "Engine/OverlapResult.h"
#include "Weapons/FPSWeapon.h"
#include "FieldGenerator.generated.h"

UCLASS()
class VGP221_A1_API AFieldGenerator : public AFPSWeapon
{
	GENERATED_BODY()

public:
	AFieldGenerator();

	UPROPERTY(EditAnywhere, Category = "Field Generator")
	float Range = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Field Generator")
	float Strength = 15.f;

	virtual void OnFire_Implementation() override;
};
