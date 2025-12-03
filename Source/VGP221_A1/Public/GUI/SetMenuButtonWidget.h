#pragma once

#include "CoreMinimal.h"
#include "GUI/ButtonWidget.h"
#include "FPSHUD.h"
#include "SetMenuButtonWidget.generated.h"

UCLASS()
class VGP221_A1_API USetMenuButtonWidget : public UButtonWidget
{
	GENERATED_BODY()

public:
	virtual void OnClick_Implementation() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMenuWidget> MenuClass = UMenuWidget::StaticClass();
};
