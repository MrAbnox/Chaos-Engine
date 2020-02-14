#ifndef COMPONENT_H
#define COMPONENT_H
class Component
{
protected:

	Component() {};
	~Component() {};

public:

	virtual void Create() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy() {};

public:

	void SetActive(bool& value);
	bool GetActive() const;

private:

	bool isActive;
};

#endif