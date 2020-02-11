#ifndef LIGHTS_H
#define LIGHTS_H

#include "GameObject.h"
#include <glm.hpp>
#include "Box.h"

enum Lights
{
	SPOTLIGHT,
	POINTLIGHT,
	DIRECTIONALLIGHT,
	FLASHLIGHT
};

class Light : public GameObject
{
public:

	Light() {};
	Light(const Lights light);
	~Light() {};

public:

	void Create();
	void Update() override;
	void Draw() override;
	void Destroy() override;

public:
	
	void SetAmbient(glm::vec3 v3);
	void SetAmbient(float x, float y, float z);

	void SetDiffuse(glm::vec3 v3);
	void SetDiffuse(float x, float y, float z);

	void SetSpecular(glm::vec3 v3);
	void SetSpecular(float x, float y, float z);

	void SetCameraPos(const glm::vec3 v3);
	void SetCameraPos(const float x, const float y, const float z);

	void SetCameraForward(const glm::vec3 v3);
	void SetCameraForward(const float x, const float y, const float z);


private:

	GLfloat m_pointSize;

private:

	glm::vec3 v3_ambient;
	glm::vec3 v3_diffuse;
	glm::vec3 v3_specular;

	glm::vec3 v3_direction;
	glm::vec3 v3_position;
	glm::vec3 v3_rgb;

	glm::vec3 v3_cameraPos;
	glm::vec3 v3_cameraFront;

private:

	float m_constant;
	float m_linear;
	float m_quadratic;

	float m_cutOff;
	float m_outerCutOff;

private:

	int m_lightNumber;

private:

	Box* m_box;
	Lights m_light;

private:

	std::vector<std::string> m_lightInformation;

private:

	static int s_pointLightsNumber;
	static int s_directionalLightNumber;
};

#endif