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

	Cube(glm::vec3 rgb);
	Cube(bool& isCubeMapped, glm::vec3 rgb, std::string filepath, std::string textureID);
	Cube(glm::vec3 rgb, std::vector<std::string> vector, std::string textureID);
	Cube(glm::vec3 rgb, std::string filepath, std::string filepath2, std::string textureID,std::string textureID2);

	~Cube();

public:

	void Create(std::string shader) override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

private:

	std::ifstream m_cubeMapUvsStream;

private:

	bool m_isCubeMapped;
};

#endif
