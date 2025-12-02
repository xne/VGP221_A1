#include "Weapons/GravityGun.h"

AGravityGun::AGravityGun()
{
	if (!PhysicsHandleComponent)
	{
		PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandleComponent"));
	}
}

void AGravityGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GrabbedComponent)
		bGrabActive = false;

	if (!bGrabActive)
		return;

	auto ComponentLocation = GrabbedComponent->GetComponentLocation();
	if (FVector::Dist(ComponentLocation, GrabLocation) > GrabRadius)
	{
		Release();
		return;
	}

	GrabLocation = GetActorLocation() + GetActorForwardVector() * GrabDistance;
	PhysicsHandleComponent->SetTargetLocationAndRotation(GrabLocation, GetActorRotation());
}

void AGravityGun::OnFire_Implementation()
{
	if (!CanFire())
		return;

	if (bGrabActive)
		Release();
	else
		Grab();

	FireTime = FireRate;
}

void AGravityGun::OnZoom_Implementation(float Value)
{
	if (!bGrabActive)
		return;
	
	GrabDistance = FMath::Clamp(GrabDistance + Value * ZoomSpeed, MinRange, MaxRange);
}

bool AGravityGun::Grab()
{
	if (bGrabActive)
		return false;

	auto Direction = GetActorRotation().Vector();

	auto Start = GetActorLocation();
	auto End = Start + (Direction * MaxRange);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	FHitResult Result;
	auto bHit = GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECC_Visibility, CollisionParams);

	if (!bHit)
		return false;

	GrabbedComponent = Result.GetComponent();
	GrabLocation = Result.ImpactPoint;
	GrabDistance = FMath::Clamp(Result.Distance, MinRange, MaxRange);

	auto &Transform = GrabbedComponent->GetComponentTransform();
	// Scale by the square root of 3 to circumscribe the grabbed component
	GrabRadius = GrabbedComponent->CalcBounds(Transform).SphereRadius * FMath::Sqrt(3.f);

	if (!GrabbedComponent->IsSimulatingPhysics())
		return false;

	PhysicsHandleComponent->GrabComponentAtLocationWithRotation(GrabbedComponent, NAME_None, GrabLocation, GetActorRotation());
	bGrabActive = true;
	OnGrab();
	return true;
}

void AGravityGun::Release()
{
	if (!bGrabActive)
		return;

	PhysicsHandleComponent->ReleaseComponent();
	bGrabActive = false;
	OnRelease();
}

bool AGravityGun::GetGrabActive() const
{
	return bGrabActive;
}

UPrimitiveComponent* AGravityGun::GetGrabbedComponent() const
{
	return GrabbedComponent;
}

FVector AGravityGun::GetGrabLocation() const
{
	return GrabLocation;
}

float AGravityGun::GetGrabDistance() const
{
	return GrabDistance;
}

float AGravityGun::GetGrabRadius() const
{
	return GrabRadius;
}
