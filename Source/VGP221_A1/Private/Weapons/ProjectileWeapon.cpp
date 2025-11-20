#include "Weapons/ProjectileWeapon.h"

AProjectileWeapon::AProjectileWeapon()
{
	if (!ProjectileClass)
	{
		ProjectileClass = AFPSProjectile::StaticClass();
	}
}

void AProjectileWeapon::OnFire_Implementation()
{
	if (!ProjectileClass)
		return;

	UWorld* World = GetWorld();
	if (!World)
		return;

	FVector FireLocation = GetActorLocation();
	FRotator FireRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, FireLocation, FireRotation, SpawnParams);
	if (!Projectile)
		return;

	FVector FireDirection = FireRotation.Vector();
	Projectile->Fire(FireDirection);
}
