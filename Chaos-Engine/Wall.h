#ifndef WALL_H
#define WALL_H

#include "Prop.h"

#include <glm.hpp>

enum WallType
{
	BRICKS = 1, BRICKS2, MIRROR
};

enum rotation
{
	LEFT = 1, RIGHT
};

class Wall : public Prop
{
private:

	Wall() {};

public:

	Wall(WallType t, rotation r, glm::vec3 position);
	~Wall();

public:

	void Create() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;
};
#endif
