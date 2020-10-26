#ifndef GRID_H
#define GRID_H

#include "GameObject.h"

class Grid: public GameObject
{

public:

	Grid(GLuint size = 10, GLfloat lineWidth = 1.0f, 
		 GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);
	~Grid();

private:

	void Create() override;

public:

	void Update() override;
	void Draw() override;
	void Destroy() override;

private:

	GLuint size;
	GLfloat lineWidth;
	GLuint totalVertices;
	GLuint totalAxisVertices;


	GLuint VAO;
	GLuint VBO_color;
	GLuint VBO_vertex;

	GLuint axisVAO;
	GLuint VBO_axisColor;
	GLuint VBO_axisVertex;

	glm::vec3 color;

	int isTextured;

	int isLit;
};

#endif

