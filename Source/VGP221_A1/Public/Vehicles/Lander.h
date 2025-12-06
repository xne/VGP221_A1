#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Vehicles/FPSVehicle.h"
#include "Lander.generated.h"

UCLASS()
class VGP221_A1_API ALander : public AFPSVehicle
{
	GENERATED_BODY()

public:
	ALander();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* BodyMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Lander")
	UPhysicsThrusterComponent* ThrusterUpComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Lander")
	UPhysicsThrusterComponent* ThrusterPitchNegativeComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Lander")
	UPhysicsThrusterComponent* ThrusterPitchPositiveComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Lander")
	UPhysicsThrusterComponent* ThrusterRollNegativeComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Lander")
	UPhysicsThrusterComponent* ThrusterRollPositiveComponent;

	UPROPERTY(EditAnywhere)
	float ThrusterUpStrength = 400000.f;

	UPROPERTY(EditAnywhere)
	float ThrusterPitchStrength = 100000.f;

	UPROPERTY(EditAnywhere)
	float ThrusterRollStrength = 100000.f;

	UFUNCTION()
	void Pitch(float Value);

	UFUNCTION()
	void Roll(float Value);

	UFUNCTION()
	void ThrusterUp(float Value);

private:
	FVector2D Input;
};
