#include "FPSProjectile.h"

AFPSProjectile::AFPSProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(15.f);
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
		if (ProjectileMeshAsset.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(ProjectileMeshAsset.Object);
		}

		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.3f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}
}

void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
