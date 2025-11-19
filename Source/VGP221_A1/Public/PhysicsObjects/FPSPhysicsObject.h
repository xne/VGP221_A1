#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectiles/FPSProjectile.h"
#include "FPSPhysicsObject.generated.h"

UCLASS()
class VGP221_A1_API AFPSPhysicsObject : public AActor
{
	GENERATED_BODY()

public:
	AFPSPhysicsObject();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "PhysicsObject")
	UStaticMeshComponent* PhysicsObjectMeshComponent;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
