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

	virtual void Create(std::string shaderRef) {}
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

	std::vector<GLint> indices;

	std::vector<GLfloat> UVs;
	std::vector<GLfloat> colors;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> tangents;
	std::vector<GLfloat> bitangents;

protected:

	GLuint VBO_color;
	GLuint VBO_normal;
	GLuint VBO_vertex;
	GLuint VBO_shadowVertex;
	GLuint VBO_texture;
	GLuint VBO_tangent;
	GLuint VBO_bitangent;

	GLuint EBO;

protected:

	GLuint ID_texture;
	GLint ID_vertex;
	GLint ID_color;
	GLint ID_normal;
	GLint ID_tangent;
	GLint ID_bitangent;

protected:

	glm::vec3 position;

private:

	char token;

protected:

	int isLit;
	int isTextured;
	int isDoubleTextured;

protected:

	Texture texture1;
	Texture texture2;
	Texture normalMap;
	Texture heightMap;

protected:

	std::ifstream indicesStream;
	std::ifstream normalsStream;
	std::ifstream verticesStream;
	std::ifstream textureUVsStream;

protected:

	bool hasNormal;
	bool hasHeightMap;
	bool isBufferDirty;

};

#endif // !PRIMITIVE_H
