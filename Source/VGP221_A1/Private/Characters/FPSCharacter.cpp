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

void AFPSCharacter::Fire()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector SpawnLocation = CameraLocation + CameraRotation.RotateVector(FireOffset);
	
	OnFire(SpawnLocation, CameraRotation);
}

void AFPSCharacter::OnFire_Implementation(FVector SpawnLocation, FRotator CameraRotation)
{
	if (!ProjectileClass)
		return;

	UWorld* World = GetWorld();
	if (!World)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, SpawnLocation, CameraRotation, SpawnParams);
	if (!Projectile)
		return;

	FVector FireDirection = CameraRotation.Vector();
	Projectile->Fire(FireDirection);
}

bool AFPSCharacter::LineTrace(float Distance, FHitResult& OutHitResult)
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector Direction = CameraRotation.Vector();

	FVector Start = CameraLocation;
	FVector End = Start + (Direction * Distance);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		Start,
		End,
		ECC_Visibility,
		CollisionParams
	);

	return bHit;
}

void AFPSCharacter::Interact()
{
	FHitResult HitResult;
	if (LineTrace(100.f, HitResult))
		if (auto FPSInteractable = Cast<AFPSInteractable>(HitResult.GetActor()))
			FPSInteractable->OnInteract();
}
