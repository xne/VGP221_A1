#include "Weapons/FieldGenerator.h"

AFieldGenerator::AFieldGenerator()
{
	bAutomatic = true;
}

void AFieldGenerator::OnFire_Implementation()
{
	if (!CanFire())
		return;

	FVector Location;
	auto Parent = GetAttachParentActor();
	if (Parent)
		Location = Parent->GetActorLocation();
	else
		Location = GetActorLocation();

	TArray<FOverlapResult> OutOverlaps;
	FCollisionQueryParams QueryParams;

	GetWorld()->OverlapMultiByObjectType(
		OutOverlaps,
		Location,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		FCollisionShape::MakeSphere(Range),
		QueryParams
	);

	for (const FOverlapResult& Overlap : OutOverlaps)
	{
		auto Component = Overlap.GetComponent();
		if (!Component)
			continue;

		FVector ClosestPoint;
		if (Component->GetClosestPointOnCollision(Location, ClosestPoint) <= 0.f)
			continue;

		auto Difference = ClosestPoint - Location;
		auto Distance = Difference.Length();
		auto Direction = Difference.GetSafeNormal();

		if (FieldMode == EFieldMode::Attractor)
			Direction = -Direction;

		auto Impulse = (Range - Distance) * Strength * Direction;
		Component->AddImpulseAtLocation(Impulse, ClosestPoint);
	}

	FireTime = FireRate;
}

void AFieldGenerator::OnSwitchMode_Implementation()
{
	switch (FieldMode)
	{
	case EFieldMode::Attractor:
		FieldMode = EFieldMode::Repeller;
		if (RepellerMaterial)
			WeaponMeshComponent->SetMaterial(0, RepellerMaterial);
		break;

	case EFieldMode::Repeller:
		FieldMode = EFieldMode::Attractor;
		if (AttractorMaterial)
			WeaponMeshComponent->SetMaterial(0, AttractorMaterial);
		break;
	}
}
