#pragma once

#include "CoreMinimal.h"
#include "GUI/ButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayButtonWidget.generated.h"

UCLASS()
class VGP221_A1_API UPlayButtonWidget : public UButtonWidget
{
	GENERATED_BODY()

public:
	virtual void OnClick_Implementation() override;
};
