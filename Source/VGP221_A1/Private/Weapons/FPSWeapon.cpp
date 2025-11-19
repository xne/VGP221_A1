#include "Weapons/FPSWeapon.h"

AFPSWeapon::AFPSWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFPSWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
