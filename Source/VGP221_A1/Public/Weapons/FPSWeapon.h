#pragma once

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "FPSWeapon.generated.h"

UCLASS()
class VGP221_A1_API AFPSWeapon : public AActor
{
	GENERATED_BODY()

public:
	AFPSWeapon();

protected:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditAnywhere)
	bool bAutomatic;

	UPROPERTY(EditAnywhere)
	float FireRate = 0.1f;

	UPROPERTY(EditAnywhere)
	float TraceLength = 10000.f;

	UFUNCTION()
	void Attach(USceneComponent* Component, FVector RelativeLocation);

	UFUNCTION()
	void Detach();

	UFUNCTION()
	bool CanFire() const;

	UFUNCTION(BlueprintPure, Category = "FPS Weapon")
	void GetFireTransform(FVector& Location, FRotator& Rotation) const;

	UFUNCTION(BlueprintNativeEvent, Category = "FPS Weapon")
	void OnFire();

	UFUNCTION(BlueprintNativeEvent, Category = "FPS Weapon")
	void OnZoom(float Value);

	UFUNCTION(BlueprintNativeEvent, Category = "FPS Weapon")
	void OnSwitchMode();

protected:
	float FireTime;
};
