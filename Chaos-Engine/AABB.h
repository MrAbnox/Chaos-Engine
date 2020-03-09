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

	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

public:

	float m_distanceFromBound;
	glm::vec3 m_distance;

	glm::vec3 m_pointOnEdge;
	glm::vec3 m_clamped;
	glm::vec3 m_halfDimension;
	glm::vec3 m_position;
	glm::vec3 m_dimension;

	float height;
	float width;
	float depth;

	glm::vec3 m_min;
	glm::vec3 m_max;

};

#endif