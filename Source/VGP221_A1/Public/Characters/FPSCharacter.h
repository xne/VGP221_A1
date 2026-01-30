#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactables/FPSInteractable.h"
#include "Projectiles/FPSProjectile.h"
#include "Vehicles/FPSVehicle.h"
#include "Weapons/FPSWeapon.h"
#include "FPSCharacter.generated.h"

UCLASS()
class VGP221_A1_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(EditAnywhere, Category = "FPS Character")
	TSubclassOf<class AFPSWeapon> FirstWeaponClass;

	UPROPERTY(EditAnywhere, Category = "FPS Character")
	FVector WeaponLocation = FVector(34.f, 34.f, -16.f);

	UPROPERTY(EditAnywhere, Category = "FPS Character")
	FRotator WeaponRotation = FRotator(0.f, 90.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "FPS Character")
	float InteractDistance = 200.f;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void FirePressed();

	UFUNCTION()
	void FireReleased();

	UFUNCTION()
	void Zoom(float Value);

	UFUNCTION()
	void SwitchMode();

	UFUNCTION()
	void Interact();

private:
	AFPSWeapon* Weapon;
	bool bFirePressed;
};
