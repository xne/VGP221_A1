#include "Weapons/FPSWeapon.h"

AFPSWeapon::AFPSWeapon()
{
	if (!WeaponMeshComponent)
	{
		WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
		if (WeaponMeshAsset.Succeeded())
		{
			WeaponMeshComponent->SetStaticMesh(WeaponMeshAsset.Object);
		}

		WeaponMeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
		WeaponMeshComponent->SetSimulatePhysics(true);
		RootComponent = WeaponMeshComponent;
	}
}

void AFPSWeapon::Attach(USceneComponent* Component, FVector RelativeLocation)
{
	WeaponMeshComponent->SetSimulatePhysics(false);
	WeaponMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponMeshComponent->AttachToComponent(Component, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	WeaponMeshComponent->SetRelativeLocation(RelativeLocation);
}

void AFPSWeapon::Detach()
{
	WeaponMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	WeaponMeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
	WeaponMeshComponent->SetSimulatePhysics(true);
}

void AFPSWeapon::OnFire_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Fire");
}

void AFPSWeapon::OnZoom_Implementation(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Zoom");
}
