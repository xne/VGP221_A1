#include "Vehicles/FPSVehicle.h"

void AFPSVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Look Horizontal", this, &AFPSVehicle::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Vertical", this, &AFPSVehicle::AddControllerPitchInput);
}
