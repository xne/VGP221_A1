#pragma once

#include "CoreMinimal.h"
#include "GUI/ButtonWidget.h"
#include "MainMenuHUD.h"
#include "BackButtonWidget.generated.h"

UCLASS()
class VGP221_A1_API UBackButtonWidget : public UButtonWidget
{
	GENERATED_BODY()

public:
	virtual void OnClick_Implementation() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenuWidget> LastMainMenuClass = UMainMenuWidget::StaticClass();
};
