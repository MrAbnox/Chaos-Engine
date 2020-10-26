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

	glm::vec3 size;
	glm::vec3 rgb;
	glm::vec3 position;

};

#endif