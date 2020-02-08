#ifndef LIGHTS_H
#define LIGHTS_H

#include "GameObject.h"
#include <glm.hpp>
#include "Box.h"

class Light : public GameObject
{
protected:

	Light() {};
	~Light() {};

public:

	void SetAmbient(glm::vec3 v3);
	void SetAmbient(glm::vec2 v2, float z);
	void SetAmbient(float x, float y, float z);

public:

	void SetDiffuse(glm::vec3 v3);
	void SetDiffuse(glm::vec2 v2, float z);
	void SetDiffuse(float x, float y, float z);

public:

	void SetSpecular(glm::vec3 v3);
	void SetSpecular(glm::vec2 v2, float z);
	void SetSpecular(float x, float y, float z);

protected:

	GLfloat m_pointSize;

protected:

	glm::vec3 v3_ambient;
	glm::vec3 v3_diffuse;
	glm::vec3 v3_specular;

	glm::vec3 v3_direction;
	glm::vec3 v3_position;
	glm::vec3 v3_rgb;

protected:

	float m_constant;
	float m_linear;
	float m_quadratic;

protected:

	Box* m_box;
};

#endif