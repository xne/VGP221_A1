#include "Interactables/Interactable.h"

AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
		CollisionComponent->InitBoxExtent(FVector(100.f));
		CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
		CollisionComponent->OnComponentHit.AddDynamic(this, &AInteractable::OnComponentHit);
		RootComponent = CollisionComponent;
	}

	if (!InteractableMeshComponent)
	{
		InteractableMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
		if (ProjectileMeshAsset.Succeeded())
		{
			InteractableMeshComponent->SetStaticMesh(ProjectileMeshAsset.Object);
		}

		InteractableMeshComponent->SetRelativeScale3D(FVector(2.f));
		InteractableMeshComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
		InteractableMeshComponent->SetupAttachment(RootComponent);
	}
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractable::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == this)
		return;

	if (OtherActor->IsA(AFPSProjectile::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Projectile hit an interactable!");
	}
}
