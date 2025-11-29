#pragma once

#include "CoreMinimal.h"
#include "Weapons/FPSWeapon.h"
#include "Projectiles/FPSProjectile.h"
#include "ProjectileWeapon.generated.h"

UCLASS()
class VGP221_A1_API AProjectileWeapon : public AFPSWeapon
{
	GENERATED_BODY()

public:
	AProjectileWeapon();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	virtual void OnFire_Implementation() override;
	virtual void OnZoom_Implementation(float Value) override;
};
