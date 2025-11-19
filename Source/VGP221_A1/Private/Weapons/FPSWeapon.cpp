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

void AFPSWeapon::OnFire_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Fire");
}

void AFPSWeapon::OnZoom_Implementation(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Zoom");
}
