#pragma once

#include "CoreMinimal.h"
#include "Engine/OverlapResult.h"
#include "Weapons/FPSWeapon.h"
#include "FieldGenerator.generated.h"

UENUM(BlueprintType)
enum class EFieldMode : uint8
{
	Attractor,
	Repeller
};

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

	UPROPERTY(EditAnywhere, Category = "Field Generator")
	UMaterialInterface* AttractorMaterial;

	UPROPERTY(EditAnywhere, Category = "Field Generator")
	UMaterialInterface* RepellerMaterial;

	virtual void OnFire_Implementation(FRotator FireRotation) override;
	virtual void OnSwitchMode_Implementation() override;

protected:
	EFieldMode FieldMode = EFieldMode::Attractor;
};
