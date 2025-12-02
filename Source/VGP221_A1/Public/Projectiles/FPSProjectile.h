#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class VGP221_A1_API AFPSProjectile : public AActor
{
	GENERATED_BODY()

public:
	AFPSProjectile();

protected:
	void BeginPlay() override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "FPS Projectile")
	UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "FPS Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "FPS Projectile")
	float Speed = 2000.f;

	UPROPERTY(EditAnywhere, Category = "FPS Projectile")
	float MaxDistance = 10000.f;

	UPROPERTY(EditAnywhere, Category = "FPS Projectile")
	float ImpactForce = 30.f;

	UFUNCTION()
	void Fire(const FVector& Direction);

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
