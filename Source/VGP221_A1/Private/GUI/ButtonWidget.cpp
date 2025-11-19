#include "GUI/ButtonWidget.h"

void UButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UButtonWidget::OnClick);
}

void UButtonWidget::OnClick_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Click");
}
