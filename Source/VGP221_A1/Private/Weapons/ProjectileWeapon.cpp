#include "Weapons/ProjectileWeapon.h"

AProjectileWeapon::AProjectileWeapon()
{
	if (!ProjectileClass)
	{
		ProjectileClass = AFPSProjectile::StaticClass();
	}

	bAutomatic = true;
	FireRate = 0.2f;
}

void AProjectileWeapon::OnFire_Implementation()
{
	if (!CanFire())
		return;

	if (!ProjectileClass)
		return;

	UWorld* World = GetWorld();
	if (!World)
		return;

	FVector FireLocation;
	FRotator FireRotation;
	GetFireTransform(FireLocation, FireRotation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	auto Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, FireLocation, FireRotation, SpawnParams);
	if (!Projectile)
		return;

	auto FireDirection = FireRotation.Vector();
	Projectile->Fire(FireDirection);

	FireTime = FireRate;
}

void AProjectileWeapon::OnZoom_Implementation(float Value)
{
}
