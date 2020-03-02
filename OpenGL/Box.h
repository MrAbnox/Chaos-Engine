#ifndef BOX_H
#define BOX_H

#include "Prop.h"

#include <glm.hpp>
#include <string>

enum boxes
{
	CRATE, LAMP, BLANK, C_SKYBOX, SKYBOX, STEELCRATE, SIMPLE
};

class Box : public Prop
{
private:

	Box() {};

public:

	Box(boxes b, glm::vec3 position);
	~Box();

public:

	void Create();
	void Update();
	void Draw();
	void Destroy();

private:

	bool isMapped;

private:

	boxes boxType_;

private:

	glm::vec3 m_size;

};

#endif