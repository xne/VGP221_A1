#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

UCLASS()
class VGP221_A1_API AFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;
};
