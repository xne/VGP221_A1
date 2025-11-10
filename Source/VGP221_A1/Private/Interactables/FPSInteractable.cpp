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

void AFPSInteractable::OnInteract_Implementation()
{
}
