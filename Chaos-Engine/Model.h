#ifndef MODEL_H
#define MODEL_H

#include "glad/glad.h"
#include "Texture.h"
#include "Buffer.h"
#include "GameObject.h"

#include <string>
#include <glm.hpp>

//struct to store all three components of a vertex group, which is
//the grouping of verts, UVs and norms for each point in a triangle
struct Groups
{
	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;
};

class Model : public GameObject
{

public:

	Model();

public:

	GLint& IsTextured();

public:

	void SetShininess(GLfloat shininess);

	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetRotation(GLfloat x, GLfloat y, GLfloat z);
	void SetScale(GLfloat x, GLfloat y, GLfloat z);

public:

	bool LoadObj(const std::string& filepath);
	bool LoadModel(const std::string& filename);
	bool LoadTexture(const std::string& filename, const std::string textureID);
	void UnloadTexture(const std::string textureID);
	void LoadNormalMap(std::string filepath);
	void LoadHeightMap(std::string filepath);

public:

	void Create(std::string shader);
	void Update();
	void Draw() override;
	void Destroy();

private:
	bool is_near(float v1, float v2);
	bool getSimilarVertexIndex(glm::vec3& in_vertex, glm::vec2& in_uv, glm::vec3& in_normal, std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, unsigned short& result);
	void indexVBO_slow(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,

		std::vector<unsigned short>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);
	void indexVBO(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,

		std::vector<GLuint>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);

	void CalculateTangents(// inputs
		std::vector<glm::vec3>& vertices,
		std::vector<glm::vec2>& uvs,
		std::vector<glm::vec3>& normals,
		// outputs
		std::vector<glm::vec3>& tangents,
		std::vector<glm::vec3>& bitangents);

private:

	GLfloat shininess;
	GLint isTextured;

private:

	GLuint VAO;
	GLuint EBO;
	GLuint vertexVBO;
	GLuint colorVBO;
	GLuint normalVBO;
	GLuint textureVBO;
	GLuint totalVertices;
	GLuint VBO_tangent;
	GLuint VBO_bitangent;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> indices;

	std::vector<GLfloat> tangents;
	std::vector<GLfloat> bitangents;

private:

	GLuint ID_vertex;
	GLuint ID_normal;
	GLuint ID_texture;
	GLuint ID_tangent;
	GLuint ID_bitangent;
	GLuint ID_color;

private:

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

private:

	glm::mat3 normal;

private:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

private:

	Texture texture;
	Texture normalMap;
	Texture heightMap;

private:

	bool firstML;

	int isHeightMapped;

	int isShadowMapped;
	int isNormalMapped;
};

#endif