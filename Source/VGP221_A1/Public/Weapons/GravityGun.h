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

	UPROPERTY(EditAnywhere)
	float GrabMaxDistance = 1000.f;

	UPROPERTY(EditAnywhere)
	float GrabMinDistance = 34.f;

	UPROPERTY(EditAnywhere)
	float ZoomSpeed = 10.f;

	UPROPERTY(VisibleAnywhere)
	bool bGrabActive;

	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent* GrabbedComponent;

	UPROPERTY(VisibleAnywhere)
	FVector GrabLocation;

	UPROPERTY(VisibleAnywhere)
	float GrabDistance;

	virtual void OnFire_Implementation() override;
	virtual void OnZoom_Implementation(float Value) override;

	UFUNCTION()
	bool Grab();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void OnGrab();

	UFUNCTION()
	void Release();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void OnRelease();
};
