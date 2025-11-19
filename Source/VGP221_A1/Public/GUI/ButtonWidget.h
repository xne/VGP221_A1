#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ButtonWidget.generated.h"

UCLASS()
class VGP221_A1_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UFUNCTION(BlueprintNativeEvent, Category = "Button")
	void OnClick();
};
