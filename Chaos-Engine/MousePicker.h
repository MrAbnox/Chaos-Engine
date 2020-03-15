#ifndef MOUSEPICKER_H
#define MOUSEPICKER_H

#include "Camera.h"
#include "AABB.h"

class MousePicker
{
public:

	MousePicker(Camera cam, glm::mat4 projection);

public:

	glm::vec3 GetCurrentRay() const;

	void Update();

private:

	glm::vec3 CalculateMouseRay();

private:

	glm::vec3 m_currentRay;

	glm::mat4 m_projection;
	glm::mat4 m_view;

	Camera* m_camera;

};

#endif