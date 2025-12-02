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

	if (FirstWeaponClass)
	{
		Weapon = GetWorld()->SpawnActor<AFPSWeapon>(FirstWeaponClass);
		Weapon->Attach(FPSCameraComponent, WeaponLocation);
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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::FirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::FireReleased);
	PlayerInputComponent->BindAxis("Zoom", this, &AFPSCharacter::Zoom);
	PlayerInputComponent->BindAction("SwitchMode", IE_Pressed, this, &AFPSCharacter::SwitchMode);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPSCharacter::Interact);
}

void AFPSCharacter::Tick(float DeltaTime)
{
	if (bFirePressed && Weapon && Weapon->bAutomatic)
		Weapon->OnFire();
}

void AFPSCharacter::MoveForward(float Value)
{
	auto Direction = GetActorForwardVector();
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	auto Direction = GetActorRightVector();
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::FirePressed()
{
	bFirePressed = true;
	if (Weapon)
		Weapon->OnFire();
}

void AFPSCharacter::FireReleased()
{
	bFirePressed = false;
}

void AFPSCharacter::Zoom(float Value)
{
	if (Weapon && !FMath::IsNearlyZero(Value, KINDA_SMALL_NUMBER))
		Weapon->OnZoom(Value);
}

void AFPSCharacter::SwitchMode()
{
	if (Weapon)
		Weapon->OnSwitchMode();
}

void AFPSCharacter::Interact()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	auto Direction = CameraRotation.Vector();
	auto Start = CameraLocation;
	auto End = Start + (Direction * InteractDistance);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FHitResult Result;
	auto bHit = GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECC_Visibility, CollisionParams);

	if (!bHit)
		return;

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
		Weapon->Attach(FPSCameraComponent, WeaponLocation);
	}
}
