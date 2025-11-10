#include "PhysicsObjects/FPSPhysicsObject.h"

AFPSPhysicsObject::AFPSPhysicsObject()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!PhysicsObjectMeshComponent)
	{
		PhysicsObjectMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PhysicsObjectMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> PhysicsObjectMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
		if (PhysicsObjectMeshAsset.Succeeded())
		{
			PhysicsObjectMeshComponent->SetStaticMesh(PhysicsObjectMeshAsset.Object);
		}

		PhysicsObjectMeshComponent->OnComponentHit.AddDynamic(this, &AFPSPhysicsObject::OnComponentHit);
		PhysicsObjectMeshComponent->SetSimulatePhysics(true);
		RootComponent = PhysicsObjectMeshComponent;
	}
}

void AFPSPhysicsObject::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSPhysicsObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSPhysicsObject::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == this)
		return;

	if (OtherActor->IsA(AFPSProjectile::StaticClass()))
	{
		FVector RelativeVelocity = OtherActor->GetVelocity() - GetVelocity();

		float Mass = OtherComponent->IsSimulatingPhysics() ? OtherComponent->GetMass() : OtherComponent->CalculateMass();

		FVector Impulse = RelativeVelocity * Mass;

		HitComponent->AddImpulseAtLocation(Impulse, Hit.ImpactPoint);
	}
}
