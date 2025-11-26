#include "Interactables/FPSInteractable.h"

AFPSInteractable::AFPSInteractable()
{
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

void AFPSInteractable::OnInteract_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Interact");
}
