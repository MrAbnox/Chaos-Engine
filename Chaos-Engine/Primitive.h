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

	void SetBufferDirty();

public:

	void SetIsLit(int x);
	void SetNormalMap(std::string filepath);
	void SetHeightMap(std::string filepath);
protected:

	void CalculateTangents();

protected:

	std::vector<GLint> m_indices;

	std::vector<GLfloat> m_UVs;
	std::vector<GLfloat> m_colors;
	std::vector<GLfloat> m_normals;
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_tangents;
	std::vector<GLfloat> m_bitangents;

protected:

	GLuint VBO_color;
	GLuint VBO_normal;
	GLuint VBO_vertex;
	GLuint VBO_shadowVertex;
	GLuint VBO_texture;
	GLuint VBO_tangent;
	GLuint VBO_bitangent;

	GLuint m_EBO;

protected:

	GLuint ID_texture;
	GLint ID_vertex;
	GLint ID_color;
	GLint ID_normal;
	GLint ID_tangent;
	GLint ID_bitangent;

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
	Texture m_normalMap;
	Texture m_heightMap;

protected:

	std::ifstream m_indicesStream;
	std::ifstream m_normalsStream;
	std::ifstream m_verticesStream;
	std::ifstream m_textureUVsStream;

protected:

	bool hasNormal;
	bool hasHeightMap;
	bool isBufferDirty;

};

#endif // !PRIMITIVE_H
