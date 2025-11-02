#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

UCLASS()
class VGP221_A1_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPSProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	UStaticMeshComponent* ProjectileMeshComponent;
};
