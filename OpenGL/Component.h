#ifndef COMPONENT_H
#define COMPONENT_H
class Component
{
public:

	Component() {};
	~Component() {};


public:

	void SetActive(bool& value);
	bool GetActive() const;

protected:

	bool isActive;
};

#endif