#pragma once

#include "CoreMinimal.h"
#include "GameStates/FPSGameState.h"
#include "Interactables/FPSInteractable.h"
#include "Terminal.generated.h"

UCLASS()
class VGP221_A1_API ATerminal : public AFPSInteractable
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInteract_Implementation() override;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* ActiveMaterial;

	UPROPERTY(EditAnywhere)
	int ActiveMaterialIdx;

private:
	bool bActive;
};
