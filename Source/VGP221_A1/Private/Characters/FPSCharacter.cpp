#include "Characters/FPSCharacter.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!FPSCameraComponent)
	{
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
		FPSCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight));
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

	GetCharacterMovement()->SetWalkableFloorAngle(60.f);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::Jump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
	PlayerInputComponent->BindAxis("Zoom", this, &AFPSCharacter::Zoom);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPSCharacter::Interact);
}

void AFPSCharacter::MoveForward(float Value)
{
	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	FVector Direction = GetActorRightVector();
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::Fire()
{
	if (Weapon)
		Weapon->OnFire();
}

void AFPSCharacter::Zoom(float Value)
{
	if (Weapon && !FMath::IsNearlyZero(Value, KINDA_SMALL_NUMBER))
		Weapon->OnZoom(Value);
}

void AFPSCharacter::Interact()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector Direction = CameraRotation.Vector();
	FVector Start = CameraLocation;
	FVector End = Start + (Direction * InteractDistance);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FHitResult Result;
	auto bHit = GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		if (auto FPSInteractable = Cast<AFPSInteractable>(Result.GetActor()))
		{
			FPSInteractable->OnInteract();
			return;
		}

		if (auto FPSWeapon = Cast<AFPSWeapon>(Result.GetActor()))
		{
			if (Weapon)
				Weapon->Detach();

			Weapon = FPSWeapon;
			Weapon->Attach(GetRootComponent(), WeaponLocation);
			return;
		}
	}
}
