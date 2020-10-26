#ifndef SPHERECOLLISION_H
#define SPHERECOLLISION_H

#include <glm.hpp>

class SphereCollision
{
public:

	SphereCollision();
	~SphereCollision();

public:

	void Draw();

public:

	bool IsColliding(const SphereCollision& second);

public:

	void SetRadius(float radius);
	void SetPosition(glm::vec3 position);

public:

	const float GetRadius();
	const glm::vec3 GetPosition();

private:

	float radius;
	float distance;
	glm::vec3 position;
	glm::vec3 distanceVector;
};

#endif