#include "Weapons/Repulsor.h"

void ARepulsor::OnFire_Implementation()
{
	if (!CanFire())
		return;

	TArray<FOverlapResult> OutOverlaps;
	FVector Location = GetActorLocation();
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
		UPrimitiveComponent* Component = Overlap.GetComponent();
		if (!Component)
			continue;

		FVector ClosestPoint;
		if (Component->GetClosestPointOnCollision(Location, ClosestPoint) <= 0.f)
			continue;

		FVector Difference = ClosestPoint - Location;
		float Distance = Difference.Length();
		FVector Direction = Difference.GetSafeNormal();

		FVector Impulse = (Range - Distance) * Strength * Direction;
		Component->AddImpulseAtLocation(Impulse, ClosestPoint);
	}

	FireTime = FireRate;
}
