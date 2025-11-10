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

void AFPSCharacter::MoveForward(float value)
{
	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveRight(float value)
{
	FVector Direction = GetActorRightVector();
	AddMovementInput(Direction, value);
}

void AFPSCharacter::GetFireLocation(FVector& Location, FRotator& Rotation)
{
	FVector CameraLocation;
	GetActorEyesViewPoint(CameraLocation, Rotation);

	Location = CameraLocation + Rotation.RotateVector(FireOffset);
}

void AFPSCharacter::Fire()
{
	FVector Location;
	FRotator CameraRotation;
	GetFireLocation(Location, CameraRotation);

	OnFire(Location, CameraRotation);
}

void AFPSCharacter::OnFire_Implementation(FVector Location, FRotator Rotation)
{
	if (!ProjectileClass)
		return;

	UWorld* World = GetWorld();
	if (!World)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, Location, Rotation, SpawnParams);
	if (!Projectile)
		return;

	FVector FireDirection = Rotation.Vector();
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

	Hit = GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		Start,
		End,
		ECC_Visibility,
		CollisionParams
	);
}

void AFPSCharacter::Interact()
{
	bool Hit;
	FHitResult Result;
	LineTrace(100.f, Hit, Result);

	if (Hit)
		if (auto FPSInteractable = Cast<AFPSInteractable>(Result.GetActor()))
			FPSInteractable->OnInteract();
}
