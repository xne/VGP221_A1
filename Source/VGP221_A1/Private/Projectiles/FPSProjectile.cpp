#include "Projectiles/FPSProjectile.h"

AFPSProjectile::AFPSProjectile()
{
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
		if (ProjectileMeshAsset.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(ProjectileMeshAsset.Object);
		}

		ProjectileMeshComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnComponentHit);
		RootComponent = ProjectileMeshComponent;
	}

	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(ProjectileMeshComponent);
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
		ProjectileMovementComponent->InitialSpeed = 2000.f;
		ProjectileMovementComponent->MaxSpeed = 2000.f;
	}

	InitialLifeSpan = 1.f;
}

void AFPSProjectile::Fire(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == this)
		return;

	if (OtherComponent->IsSimulatingPhysics())
	{
		auto RelativeVelocity = GetVelocity() - OtherActor->GetVelocity();
		auto Impulse = RelativeVelocity * ImpactForceMult;
		OtherComponent->AddImpulseAtLocation(Impulse, Hit.ImpactPoint);
	}

	Destroy();
}
