#pragma once

#include "CoreMinimal.h"
#include "GUI/ButtonWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "QuitButtonWidget.generated.h"

UCLASS()
class VGP221_A1_API UQuitButtonWidget : public UButtonWidget
{
	GENERATED_BODY()

public:
	virtual void OnClick_Implementation() override;
};
