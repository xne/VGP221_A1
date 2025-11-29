#pragma once

#include "CoreMinimal.h"
#include "Triggerables/FPSTriggerable.h"
#include "Forcefield.generated.h"

UENUM(BlueprintType)
enum class EFadeState : uint8
{
	None,
	In,
	Out
};

UCLASS()
class VGP221_A1_API AForcefield : public AFPSTriggerable
{
	GENERATED_BODY()

public:
	AForcefield();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Forcefield")
	UStaticMeshComponent* ForcefieldMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Forcefield")
	float FadeTime = 0.25f;

	UFUNCTION(BlueprintCallable)
	void FadeIn();

	UFUNCTION(BlueprintCallable)
	void FadeOut();

	virtual void OnTrigger_Implementation() override;

private:
	UMaterialInstanceDynamic* ForcefieldMaterial;
	EFadeState FadeState = EFadeState::None;
	float LinearOpacity = 1.f;
};
