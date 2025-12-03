#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GUI/MenuWidget.h"
#include "FPSHUD.generated.h"

UCLASS()
class VGP221_A1_API AFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	void PushMenu(TSubclassOf<UMenuWidget> MenuClass);
	void PopMenu();

private:
	UMenuWidget* MenuWidget;
};
