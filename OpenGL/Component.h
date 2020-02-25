#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component
{
public:

	Component() {};
	~Component() {};


public:

	void SetActive(const bool& value);
	bool GetActive() const;

public:

	const std::string const GetName() const;

protected:

	bool isActive;

protected:

	std::string m_name;
};

#endif