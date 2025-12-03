#pragma once

#include "CoreMinimal.h"
#include "FPSGameInstance.h"
#include "GUI/FPSHUD.h"
#include "GUI/MenuWidget.h"
#include "MainMenuHUD.generated.h"

UCLASS()
class VGP221_A1_API AMainMenuHUD : public AFPSHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMenuWidget> MainMenuClass = UMenuWidget::StaticClass();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMenuWidget> GameOverClass;
};
