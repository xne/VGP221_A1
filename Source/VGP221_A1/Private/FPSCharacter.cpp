#include "FPSCharacter.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!FPSCameraComponent)
	{
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
		FPSCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f + BaseEyeHeight));
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

	if (!ProjectileClass)
	{
		ProjectileClass = AFPSProjectile::StaticClass();
	}
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
	if (!ProjectileClass)
		return;

	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	UWorld* World = GetWorld();
	if (!World)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, CameraLocation, CameraRotation, SpawnParams);
	if (!Projectile)
		return;

	FVector FireDirection = CameraRotation.Vector();
	Projectile->Fire(FireDirection);
}
