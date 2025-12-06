#include "Vehicles/Lander.h"

ALander::ALander()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!BodyMeshComponent)
	{
		BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshAsset(TEXT("/Engine/BasicShapes/Cylinder"));
		if (BodyMeshAsset.Succeeded())
		{
			BodyMeshComponent->SetStaticMesh(BodyMeshAsset.Object);
		}

		BodyMeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
		BodyMeshComponent->SetSimulatePhysics(true);
		RootComponent = BodyMeshComponent;
	}

	if (!ThrusterUpComponent)
	{
		ThrusterUpComponent = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ThrusterUp"));
		ThrusterUpComponent->ThrustStrength = 0.f;
		ThrusterUpComponent->SetAutoActivate(true);

		ThrusterUpComponent->SetupAttachment(RootComponent);
	}

	if (!ThrusterPitchNegativeComponent)
	{
		ThrusterPitchNegativeComponent = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ThrusterPitchNegative"));
		ThrusterPitchNegativeComponent->ThrustStrength = 0.f;
		ThrusterPitchNegativeComponent->SetAutoActivate(true);

		ThrusterPitchNegativeComponent->SetupAttachment(RootComponent);
	}

	if (!ThrusterPitchPositiveComponent)
	{
		ThrusterPitchPositiveComponent = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ThrusterPitchPositive"));
		ThrusterPitchPositiveComponent->ThrustStrength = 0.f;
		ThrusterPitchPositiveComponent->SetAutoActivate(true);

		ThrusterPitchPositiveComponent->SetupAttachment(RootComponent);
	}

	if (!ThrusterRollNegativeComponent)
	{
		ThrusterRollNegativeComponent = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ThrusterRollNegative"));
		ThrusterRollNegativeComponent->ThrustStrength = 0.f;
		ThrusterRollNegativeComponent->SetAutoActivate(true);

		ThrusterRollNegativeComponent->SetupAttachment(RootComponent);
	}

	if (!ThrusterRollPositiveComponent)
	{
		ThrusterRollPositiveComponent = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ThrusterRollPositive"));
		ThrusterRollPositiveComponent->ThrustStrength = 0.f;
		ThrusterRollPositiveComponent->SetAutoActivate(true);

		ThrusterRollPositiveComponent->SetupAttachment(RootComponent);
	}
}

void ALander::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Pitch", this, &ALander::Pitch);
	PlayerInputComponent->BindAxis("Roll", this, &ALander::Roll);
	PlayerInputComponent->BindAxis("Thruster Up", this, &ALander::ThrusterUp);
}

void ALander::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlYaw = GetControlRotation().Yaw;
	auto ControlSpaceInput = Input.GetRotated(ControlYaw);

	ThrusterPitchPositiveComponent->ThrustStrength = FMath::Max(0.f, ControlSpaceInput.X) * ThrusterPitchStrength;
	ThrusterPitchNegativeComponent->ThrustStrength = FMath::Abs(FMath::Min(0.f, ControlSpaceInput.X)) * ThrusterPitchStrength;

	ThrusterRollPositiveComponent->ThrustStrength = FMath::Max(0.f, ControlSpaceInput.Y) * ThrusterRollStrength;
	ThrusterRollNegativeComponent->ThrustStrength = FMath::Abs(FMath::Min(0.f, ControlSpaceInput.Y)) * ThrusterRollStrength;
}

void ALander::Pitch(float Value)
{
	Input.X = Value;
}

void ALander::Roll(float Value)
{
	Input.Y = Value;
}

void ALander::ThrusterUp(float Value)
{
	if (ThrusterUpComponent)
		ThrusterUpComponent->ThrustStrength = Value * ThrusterUpStrength;
}
