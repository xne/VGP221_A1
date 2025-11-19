#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactables/FPSInteractable.h"
#include "Projectiles/FPSProjectile.h"
#include "FPSCharacter.generated.h"

UCLASS()
class VGP221_A1_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	FVector FireOffset = FVector(0.f, 100.f, -32.f);

	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void Fire();

	UFUNCTION(BlueprintPure)
	void GetFireLocation(FVector& FireLocation, FRotator& FireRotation);

	UFUNCTION(BlueprintNativeEvent, Category = "Character")
	void OnFire();

	UFUNCTION(BlueprintCallable)
	void LineTrace(float Distance, bool& Hit, FHitResult& Result);

	UFUNCTION()
	void Interact();
};
