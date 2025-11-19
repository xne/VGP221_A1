#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GUI/MainMenuWidget.h"
#include "MainMenuHUD.generated.h"

UCLASS()
class VGP221_A1_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenuWidget> FirstMainMenuClass;
	UMainMenuWidget* MainMenuWidget;

	void PushMainMenu(TSubclassOf<UMainMenuWidget> MainMenuClass);
	void PopMainMenu();
};
