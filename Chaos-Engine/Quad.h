#ifndef QUAD_H
#define QUAD_H

#include "Primitive.h"
#include "Texture.h"

#include <glm.hpp>
#include <SDL.h>
#include <string>
#include <gtc/matrix_transform.hpp>
#include <vector>

class Quad: public Primitive
{

public:

	Quad();
	Quad(std::string& filepath, std::string textureID);
	Quad(std::string& filepath, std::string& filepath2, std::string textureID, std::string textureID2);

public:

	~Quad();

public:

	void Create(std::string shader) override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

private:

	const unsigned int SHADOW_WIDTH = 1024;
	const unsigned int SHADOW_HEIGHT = 1024;

	glm::mat4 lightView;
	glm::mat4 lightProjection;
	glm::mat4 lightSpaceMatrix;

	const float near_plane = 1.0f;
	const float far_plane = 7.5f;

	int time = 0;
};

#endif
