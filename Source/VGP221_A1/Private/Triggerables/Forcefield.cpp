#include "Triggerables/Forcefield.h"

AForcefield::AForcefield()
{
	PrimaryActorTick.bCanEverTick = true;

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

void AForcefield::BeginPlay()
{
	Super::BeginPlay();

	if (ForcefieldMeshComponent)
		ForcefieldMaterial = ForcefieldMeshComponent->CreateDynamicMaterialInstance(0);
}

void AForcefield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (FadeState)
	{
	case EFadeState::In:
		LinearOpacity = FMath::FInterpConstantTo(LinearOpacity, 1.f, DeltaTime, 1.f / FadeTime);

		if (FMath::IsNearlyEqual(LinearOpacity, 1.f, KINDA_SMALL_NUMBER))
		{
			LinearOpacity = 1.f;
			FadeState = EFadeState::None;
		}

		break;
	case EFadeState::Out:
		LinearOpacity = FMath::FInterpConstantTo(LinearOpacity, 0.f, DeltaTime, 1.f / FadeTime);

		if (FMath::IsNearlyZero(LinearOpacity, KINDA_SMALL_NUMBER))
		{
			LinearOpacity = 0.f;
			FadeState = EFadeState::None;
			SetActorEnableCollision(false);
		}

		break;
	}

	if (ForcefieldMaterial)
	{
		// Apply exponential interpolation to counteract the non-linear behavior of Fresnel
		auto Opacity = FMath::InterpExpoIn(0.f, 1.f, LinearOpacity);
		ForcefieldMaterial->SetScalarParameterValue(FName("Opacity"), Opacity);
	}
}

void AForcefield::FadeIn()
{
	FadeState = EFadeState::In;
	SetActorEnableCollision(true);
}

void AForcefield::FadeOut()
{
	FadeState = EFadeState::Out;
}

void AForcefield::OnTrigger_Implementation()
{
	if (FadeState == EFadeState::Out || FadeState == EFadeState::None && FMath::IsNearlyZero(LinearOpacity, KINDA_SMALL_NUMBER))
	{
		FadeIn();
	}
	else
	{
		FadeOut();
	}
}
