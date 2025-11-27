#include "Triggerables/FPSTriggerable.h"

void AFPSTriggerable::Trigger()
{
	OnTrigger();
}

void AFPSTriggerable::OnTrigger_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Trigger");
}
