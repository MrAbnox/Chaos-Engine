#ifndef LIGHT_H
#define LIGHT_H

#include "Light.h"
#include "Cube.h"

#include <vector>

class PointLight : public Light
{
public:

	PointLight(glm::vec3 position, int lightNumber, int lightColor);
	~PointLight();

public:

	void Create() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

private:

	int m_lightNumber;

	std::vector<std::string> m_lightInformation;

};

#endif