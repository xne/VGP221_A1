#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GUI/GameMenuWidget.h"
#include "FPSHUD.generated.h"

UCLASS()
class VGP221_A1_API AFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameMenuWidget> FirstGameMenuClass = UGameMenuWidget::StaticClass();
	UGameMenuWidget* GameMenuWidget;

	void PushGameMenu(TSubclassOf<UGameMenuWidget> GameMenuClass);
	void PopGameMenu();
};
