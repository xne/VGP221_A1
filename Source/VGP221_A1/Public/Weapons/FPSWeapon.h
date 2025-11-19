#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeapon.generated.h"

UCLASS()
class VGP221_A1_API AFPSWeapon : public AActor
{
	GENERATED_BODY()

public:
	AFPSWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
