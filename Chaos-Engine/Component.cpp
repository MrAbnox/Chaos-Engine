#include "Component.h"

void Component::SetActive(const bool& value)
{
	isActive = value;
}

bool Component::GetActive() const
{
	return isActive;
}

std::string const Component::GetName() const
{
	return name;
}
