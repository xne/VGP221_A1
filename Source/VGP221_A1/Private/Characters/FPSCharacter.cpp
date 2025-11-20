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

	if (!ProjectileClass)
	{
		ProjectileClass = AFPSProjectile::StaticClass();
	}

	GetCharacterMovement()->SetWalkableFloorAngle(60.f);
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void AFPSCharacter::GetFireLocation(FVector& FireLocation, FRotator& FireRotation)
{
	FVector CameraLocation;
	GetActorEyesViewPoint(CameraLocation, FireRotation);

	FireLocation = CameraLocation + FireRotation.RotateVector(FireOffset);
}

void AFPSCharacter::Fire()
{
	OnFire();
}

void AFPSCharacter::OnFire_Implementation()
{
	if (!ProjectileClass)
		return;

	UWorld* World = GetWorld();
	if (!World)
		return;

	FVector FireLocation;
	FRotator FireRotation;
	GetFireLocation(FireLocation, FireRotation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, FireLocation, FireRotation, SpawnParams);
	if (!Projectile)
		return;

	FVector FireDirection = FireRotation.Vector();
	Projectile->Fire(FireDirection);
}

void AFPSCharacter::LineTrace(float Distance, bool& Hit, FHitResult& OutHitResult)
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector Direction = CameraRotation.Vector();

	FVector Start = CameraLocation;
	FVector End = Start + (Direction * Distance);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	Hit = GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, CollisionParams);
}

void AFPSCharacter::Interact()
{
	bool Hit;
	FHitResult Result;
	LineTrace(InteractDistance, Hit, Result);

	if (Hit)
	{
		if (auto FPSInteractable = Cast<AFPSInteractable>(Result.GetActor()))
		{
			FPSInteractable->OnInteract();
			return;
		}

		if (auto FPSWeapon = Cast<AFPSWeapon>(Result.GetActor()))
		{
			FPSWeapon->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			return;
		}
	}
}
