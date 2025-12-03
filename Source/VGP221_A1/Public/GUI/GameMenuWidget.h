#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GUI/MenuWidget.h"
#include "GameMenuWidget.generated.h"

UCLASS()
class VGP221_A1_API UGameMenuWidget : public UMenuWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UFUNCTION()
	void UpdateHealthBar(float HealthPercent);

	UFUNCTION()
	void UpdateTimeText(int Time);

	UFUNCTION()
	void UpdateScoreText(int Score);
};
