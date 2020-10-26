#ifndef FLOOR_H
#define FLOOR_H


#include "Prop.h"

enum TYPE
{
	GRASS = 0, TILED, WOOD, STONE, EMPTY, WATER
};
class Floor : public Prop
{
private:

	Floor() {};

public:

	Floor(TYPE t, glm::vec3 position);
	~Floor();

public:

	void Create() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;
};

#endif