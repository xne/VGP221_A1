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

	FVector ComponentLocation = GrabbedComponent->GetComponentLocation();
	float Margin = GrabbedComponent->GetLocalBounds().SphereRadius + GrabMargin;

	if (FVector::Dist(ComponentLocation, GrabLocation) > Margin)
	{
		Release();
		return;
	}

	GrabLocation = GetActorLocation() + GetActorForwardVector() * GrabDistance;
	PhysicsHandleComponent->SetTargetLocationAndRotation(GrabLocation, GetActorRotation());
}

void AGravityGun::OnFire_Implementation()
{
	if (bGrabActive)
		Release();
	else
		Grab();
}

void AGravityGun::OnZoom_Implementation(float Value)
{
	if (!bGrabActive)
		return;
	
	GrabDistance = FMath::Clamp(GrabDistance + Value * ZoomSpeed, GrabMinDistance, GrabMaxDistance);
}

bool AGravityGun::Grab()
{
	if (bGrabActive)
		return false;

	FVector Direction = GetActorRotation().Vector();

	FVector Start = GetActorLocation();
	FVector End = Start + (Direction * GrabMaxDistance);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	FHitResult Result;
	auto bHit = GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECC_Visibility, CollisionParams);

	if (!bHit)
		return false;

	GrabbedComponent = Result.GetComponent();
	GrabLocation = Result.ImpactPoint;
	GrabDistance = FMath::Clamp(Result.Distance, GrabMinDistance, GrabMaxDistance);

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

UPrimitiveComponent* AGravityGun::GetGrabbedComponent()
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
