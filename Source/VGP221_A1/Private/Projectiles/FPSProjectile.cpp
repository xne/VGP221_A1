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
	}
}

void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	
	SetLifeSpan(MaxDistance / Speed);
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
		auto Impulse = RelativeVelocity * ImpactForce;
		OtherComponent->AddImpulseAtLocation(Impulse, Hit.ImpactPoint);
	}

	Destroy();
}
