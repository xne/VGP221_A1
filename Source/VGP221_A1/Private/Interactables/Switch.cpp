#include "Interactables/Switch.h"

void ASwitch::OnInteract_Implementation()
{
	if (Triggerable)
		Triggerable->OnTrigger();
}
