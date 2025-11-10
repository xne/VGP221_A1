#include "Interactables/FPSInteractable.h"

AFPSInteractable::AFPSInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!InteractableMeshComponent)
	{
		InteractableMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> InteractableMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
		if (InteractableMeshAsset.Succeeded())
		{
			InteractableMeshComponent->SetStaticMesh(InteractableMeshAsset.Object);
		}

		InteractableMeshComponent->OnComponentHit.AddDynamic(this, &AFPSInteractable::OnComponentHit);
		RootComponent = InteractableMeshComponent;
	}
}

void AFPSInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSInteractable::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == this)
		return;

	if (OtherActor->IsA(AFPSProjectile::StaticClass()))
		OnInteract();
}

void AFPSInteractable::OnInteract_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Projectile hit an interactable!");
}
