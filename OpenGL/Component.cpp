#include "Component.h"

void Component::SetActive(bool& value)
{
	isActive = value;
}

bool Component::GetActive() const
{
	return isActive;
}
