#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactables/FPSInteractable.h"
#include "Projectiles/FPSProjectile.h"
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

public:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFPSWeapon> FirstWeaponClass;
	AFPSWeapon* Weapon;

	UPROPERTY(EditAnywhere)
	FVector WeaponLocation = FVector(0.f, 100.f, -32.f);

	UPROPERTY(EditAnywhere)
	float InteractDistance = 200.f;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Zoom(float Value);

	UFUNCTION()
	void Interact();
};
