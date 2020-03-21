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

	Cube(std::string shader);
	Cube(bool isCubeMapped, std::string filepath, std::string textureID, std::string shader);
	Cube(std::vector<std::string>& vector, std::string textureID, std::string shader);
	Cube(std::string filepath, std::string filepath2, std::string textureID, std::string textureID2, std::string shader);

	~Cube();

public:

	void Create(std::string shader);
	void Update() override;
	void Draw() override;
	void Destroy() override;

private:

	std::ifstream m_cubeMapUvsStream;

private:

	bool m_isCubeMapped;

	static Texture s_skyBoxTexture;
};

#endif
