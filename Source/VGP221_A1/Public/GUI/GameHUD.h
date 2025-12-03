#pragma once

#include "CoreMinimal.h"
#include "GUI/FPSHUD.h"
#include "GUI/MenuWidget.h"
#include "GameHUD.generated.h"

UCLASS()
class VGP221_A1_API AGameHUD : public AFPSHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMenuWidget> GameMenuClass = UMenuWidget::StaticClass();
};
