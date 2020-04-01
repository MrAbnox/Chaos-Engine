#ifndef RAY_H
#define RAY_H

#include <glm.hpp>

class Ray
{
public:
	Ray(const glm::vec3& origin, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
	~Ray();

public:

	glm::vec3 GetDirection();
private:

	glm::vec3 m_direction;
	glm::vec3 m_origin;
};

#endif

