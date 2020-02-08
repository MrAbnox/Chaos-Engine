#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"

class SpotLight : public Light
{
public:

	SpotLight(glm::vec3 initialposition);
	~SpotLight();

public:

	void Create() override;
	void Update(glm::vec3 cameraposition, glm::vec3 camerafront);
	void Draw() override;
	void Destroy() override;

private:

	float m_cutOff;
	float m_outerCutOff;

};

#endif // !LAMPLIGHT_H