#ifndef AABB_H
#define AABB_H

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
//#include "DebugManager.h"
#include "SphereCollision.h"


class AABB
{
public:
	AABB();
	~AABB();

public:

	void SetPosition(float x, float y, float z);
	void SetDimension(float width, float height, float depth);

public:

	bool IsColliding(const AABB& secondBox);
	bool IsColliding(SphereCollision& second);

public:

	glm::vec3 GetMin();
	glm::vec3 GetMax();

public:

	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

public:

	float distanceFromBound;
	glm::vec3 distance;

	glm::vec3 pointOnEdge;
	glm::vec3 clamped;
	glm::vec3 halfDimension;
	glm::vec3 position;
	glm::vec3 dimension;

	float height;
	float width;
	float depth;

	glm::vec3 min;
	glm::vec3 max;

};

#endif