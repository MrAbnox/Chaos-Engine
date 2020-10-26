#ifndef PHYSICS_H
#define PHYSICS_H

#include "AABB.h"

class Physics
{
public:

	Physics();

public:

	bool RayABB(glm::vec3 dir, glm::vec3 pos, AABB aabb);
};

#endif