#ifndef SKYBOX_H
#define SKYBOX_H
#include "GameObject.h"
#include "Cube.h"
class SkyBox : public GameObject
{
public:

	SkyBox();
	~SkyBox();

public:

	void Create() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

private:

	Cube* box;

private:

	glm::vec3 v3_size;
	glm::vec3 v3_rgb;
	glm::vec3 v3_position;

};

#endif