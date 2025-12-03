#include "GUI/PlayButtonWidget.h"

void UPlayButtonWidget::OnClick_Implementation()
{
	UGameplayStatics::OpenLevel(this, Levels::World);
}
