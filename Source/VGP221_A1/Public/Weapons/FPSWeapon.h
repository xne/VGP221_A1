#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeapon.generated.h"

UCLASS()
class VGP221_A1_API AFPSWeapon : public AActor
{
	GENERATED_BODY()

public:
	AFPSWeapon();

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* WeaponMeshComponent;

	UFUNCTION()
	void Attach(USceneComponent* Component, FVector RelativeLocation);

	UFUNCTION()
	void Detach();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void OnFire();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void OnZoom(float Value);
};
