#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectiles/FPSProjectile.h"
#include "FPSInteractable.generated.h"

UCLASS()
class VGP221_A1_API AFPSInteractable : public AActor
{
	GENERATED_BODY()
	
public:
	AFPSInteractable();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Interactable")
	UStaticMeshComponent* InteractableMeshComponent;

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnInteract();
};
