#include "Weapons/FPSWeapon.h"

AFPSWeapon::AFPSWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

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

void AFPSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(FireTime, KINDA_SMALL_NUMBER))
		FireTime = FMath::FInterpConstantTo(FireTime, 0.f, DeltaTime, 1.f);
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

bool AFPSWeapon::CanFire() const
{
	return FMath::IsNearlyZero(FireTime, KINDA_SMALL_NUMBER);
}

void AFPSWeapon::OnFire_Implementation()
{
	if (!CanFire())
		return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Fire");

	FireTime = FireRate;
}

void AFPSWeapon::OnZoom_Implementation(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Zoom");
}
