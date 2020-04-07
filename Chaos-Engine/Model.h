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

class Model: public GameObject
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
	bool getSimilarVertexIndex(glm::vec3& in_vertex, glm::vec2& in_uv, glm::vec3& in_normal,std::vector<glm::vec3>& out_vertices,
							   std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals,unsigned short& result);
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

	GLfloat m_shininess;
	GLint m_isTextured;

private:

	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_vertexVBO;
	GLuint m_colorVBO;
	GLuint m_normalVBO;
	GLuint m_textureVBO;
	GLuint m_totalVertices;
	GLuint VBO_tangent;
	GLuint VBO_bitangent;

	std::vector<glm::vec3> test_vertices;
	std::vector<glm::vec2> test_uvs;
	std::vector<glm::vec3> test_normals;
	std::vector<GLuint> test_indices;

	std::vector<GLfloat> m_tangents;
	std::vector<GLfloat> m_bitangents;

private:

	GLuint ID_vertex;
	GLuint ID_normal;
	GLuint ID_texture;
	GLuint ID_tangent;
	GLuint ID_bitangent;
	GLuint ID_color;

private:

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

private:

	glm::mat3 m_normal;

private:

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	
private:

	Texture m_texture;
	Texture m_normalMap;
	Texture m_heightMap;

private:

	bool m_firstML;

	int m_isHeightMapped;

	int m_isShadowMapped;
	int m_isNormalMapped;
};

#endif