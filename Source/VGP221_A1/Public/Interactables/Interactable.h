#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Projectiles/FPSProjectile.h"
#include "Interactable.generated.h"

UCLASS()
class VGP221_A1_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:
	AInteractable();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Interactable")
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Interactable")
	UStaticMeshComponent* InteractableMeshComponent;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
