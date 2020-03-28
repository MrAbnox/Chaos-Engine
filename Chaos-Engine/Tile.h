#ifndef TILE_H
#define TILE_H
#include "GameObject.h"
#include "Texture.h"

class Tile : public GameObject
{
public: 

	Tile(GLfloat width = 1.0f, GLfloat height = 1.0f, GLuint spriteSheetCol = 1, GLuint spriteSheetRow = 1);
	~Tile();

public:

	void Create() override;
	void Draw() override;

public:

	void SetTile(GLuint column, GLuint row);
	void LoadTexture(std::string filepath, std::string textureID);
	
private:

	Texture m_texture;

private:

	GLuint m_tileIndex;
	GLuint m_spriteSheetCol;
	GLuint m_spriteSheetRow;

	GLint ID_color;
	GLint ID_vertex;
	GLint ID_texture;
private:  

	GLuint m_colorVBO;
	GLuint m_vertexVBO;
	GLuint m_textureVBO;
	GLuint m_EBO;

private:

	int offSetColor;
	int offSetVert;

private:
	
	GLuint offsetUV = 0;
	GLuint offsetVert = 0;
	GLuint offsetColor = 0;
	GLuint offsetIndex = 0;

private:

	glm::vec2 halfDimension;
	glm::vec4 m_color;

private:

	const int BYTES_PER_TILE_UV = 8 * sizeof(GLfloat);
	const int BYTES_PER_TILE_COLOR = 16 * sizeof (GLfloat);
	const int BYTES_PER_TILE_VERTEX = 12 * sizeof(GLfloat);
	const int BYTES_PER_TILE_INDEX = 6 * sizeof (GLuint);

	const int TOTAL_DIMENSION = m_spriteSheetCol * m_spriteSheetRow;
	const int TOTAL_BYTES_VBO_VERT = TOTAL_DIMENSION * BYTES_PER_TILE_VERTEX;
	const int TOTAL_BYTES_VBO_COLOR = TOTAL_DIMENSION * BYTES_PER_TILE_COLOR;
	const int TOTAL_BYTES_VBO_UV = TOTAL_DIMENSION * BYTES_PER_TILE_UV;
	const int TOTAL_BYTES_EBO = TOTAL_DIMENSION * BYTES_PER_TILE_INDEX;
};

#endif