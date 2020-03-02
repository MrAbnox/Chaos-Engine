#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Texture.h"
#include "GameObject.h"

#include <fstream>

class Primitive : 
	public GameObject
{
public:

	Primitive();
	~Primitive() {}

public:

	virtual void Create(std::string shader) {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void Destroy() {};

protected:

	enum Files
	{
		INDICES, VERTICES, UVS, NORMALS
	};

protected:

	void ReadFile(std::string filepath, Files f);

public:

	void SendShineData();
	void SendAmbientData();
	void SendDiffuseData();
	void SendSpecularData();

public:

	void SetIsLit(int x);

protected:

	std::vector<GLint> m_indices;

	std::vector<GLfloat> m_UVs;
	std::vector<GLfloat> m_colors;
	std::vector<GLfloat> m_normals;
	std::vector<GLfloat> m_vertices;

protected:

	GLuint VBO_color;
	GLuint VBO_normal;
	GLuint VBO_vertex;
	GLuint VBO_texture;

	GLuint m_EBO;
	GLuint m_VAO;


protected:

	GLuint ID_texture;
	GLint ID_vertex;
	GLint ID_color;
	GLint ID_normal;

protected:

	glm::vec3 v3_position;

private:

	char token;

protected:

	int m_isLit;
	int m_isTextured;
	int isDoubleTextured;

protected:

	Texture m_texture1;
	Texture m_texture2;

protected:

	std::ifstream m_indicesStream;
	std::ifstream m_normalsStream;
	std::ifstream m_verticesStream;
	std::ifstream m_textureUVsStream;

};

#endif // !PRIMITIVE_H
