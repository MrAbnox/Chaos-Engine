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
public:

	void Create(std::string shader);
	void Update();
	void Draw();
	void Destroy();

private:
	bool is_near(float v1, float v2);
	bool getSimilarVertexIndex(glm::vec3& in_vertex, glm::vec2& in_uv, glm::vec3& in_normal,std::vector<glm::vec3>& out_vertices,
							   std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals,unsigned short& result);

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

private:

	GLuint m_vertexAttributeID;
	GLuint m_normalAttributeID;
	GLuint m_textureAttributeID;

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
};

#endif