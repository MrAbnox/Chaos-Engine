#ifndef CUBE_H
#define CUBE_H

#include "glad/glad.h"
#include "Primitive.h"
#include "Texture.h"

#include <SDL.h>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

class Cube :  public Primitive
{
private:

	Cube();

public:

	Cube(std::string shaderRef);
	Cube(bool isCubeMapped, std::string filepath, std::string textureID);
	Cube(std::vector<std::string>& vector, std::string textureID);
	Cube(std::string filepath, std::string filepath2, std::string textureID, std::string textureID2);

	~Cube();

public:

	void Create(std::string shaderRef);
	void Update() override;
	void Draw() override;
	void Destroy() override;

private:

	std::ifstream cubeMapUvsStream;

private:

	bool isCubeMapped;
	static Texture skyBoxTexture;
};

#endif
