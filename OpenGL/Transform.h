#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>

class Transform
{

public:

	Transform();

	glm::mat4 operator*(const glm::mat4& second);

public:

	void SetIdentity();

public:

	void Translate(glm::vec3& v3);
	void Translate(glm::vec2& v2, float& z);
	void Translate(float& x, float& y, float& z);

	void Rotate(float& angle, glm::vec3& v3);
	void Rotate(float& angle, glm::vec2& v2, float& z);
	void Rotate(float& angle, float& x, float& y, float& z);

	void Scale(glm::vec3& v3);
	void Scale(glm::vec2& v2, float& z);
	void Scale(float& x, float& y, float& z);

public:

	glm::mat4 GetModel();

private:

	glm::mat4 m_model;

};


#endif
 