#include "Triggerables/Forcefield.h"

AForcefield::AForcefield()
{
	if (!ForcefieldMeshComponent)
	{
		ForcefieldMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ForcefieldMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> ForcefieldMeshAsset(TEXT("/Engine/BasicShapes/Plane"));
		if (ForcefieldMeshAsset.Succeeded())
		{
			ForcefieldMeshComponent->SetStaticMesh(ForcefieldMeshAsset.Object);
		}

		RootComponent = ForcefieldMeshComponent;
	}
}

void AForcefield::OnTrigger_Implementation()
{
	if (IsHidden())
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}
