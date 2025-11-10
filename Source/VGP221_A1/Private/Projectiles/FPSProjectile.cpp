#include "Projectiles/FPSProjectile.h"

AFPSProjectile::AFPSProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

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
		ProjectileMovementComponent->InitialSpeed = BulletSpeed;
		ProjectileMovementComponent->MaxSpeed = BulletSpeed;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	InitialLifeSpan = 1.5f;
}

void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSProjectile::Fire(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == this)
		return;

	Destroy();
}
