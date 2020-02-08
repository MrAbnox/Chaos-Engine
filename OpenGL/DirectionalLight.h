#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "Light.h"
class DirectionalLight : public Light
{
public:

	DirectionalLight();
	~DirectionalLight();

public:

	void Create() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

};

#endif