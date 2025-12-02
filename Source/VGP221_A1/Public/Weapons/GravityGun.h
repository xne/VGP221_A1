#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Weapons/FPSWeapon.h"
#include "GravityGun.generated.h"

UCLASS()
class VGP221_A1_API AGravityGun : public AFPSWeapon
{
	GENERATED_BODY()

public:
	AGravityGun();

protected:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly)
	UPhysicsHandleComponent* PhysicsHandleComponent;

	UPROPERTY(EditAnywhere, Category = "Gravity Gun")
	float MinRange = 150.f;

	UPROPERTY(EditAnywhere, Category = "Gravity Gun")
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Gravity Gun")
	float ZoomSpeed = 10.f;

	virtual void OnFire_Implementation() override;
	virtual void OnZoom_Implementation(float Value) override;

	UFUNCTION()
	bool Grab();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gravity Gun")
	void OnGrab();

	UFUNCTION()
	void Release();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gravity Gun")
	void OnRelease();

	UFUNCTION(BlueprintPure, Category = "Gravity Gun")
	bool GetGrabActive() const;

	UFUNCTION(BlueprintPure, Category = "Gravity Gun")
	UPrimitiveComponent* GetGrabbedComponent() const;

	UFUNCTION(BlueprintPure, Category = "Gravity Gun")
	FVector GetGrabLocation() const;

	UFUNCTION(BlueprintPure, Category = "Gravity Gun")
	float GetGrabDistance() const;

	UFUNCTION(BlueprintPure, Category = "Gravity Gun")
	float GetGrabRadius() const;

private:
	bool bGrabActive;
	UPrimitiveComponent* GrabbedComponent;
	FVector GrabLocation;
	float GrabDistance;
	float GrabRadius;
};
