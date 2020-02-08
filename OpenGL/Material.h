#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm.hpp>
#include <string>

enum Materials
{
	M_AMBIENT = 0, M_SPECULAR, M_DIFFUSE, M_SHINE
};	
class Material
{
public:

	Material();
	~Material();

public:

	void SendData(Materials m, std::string shader);

public:

	void SetAmbient(glm::vec3 v3);
	void SetAmbient(glm::vec2 v2, float z);
	void SetAmbient(float x, float y, float z);

public:

	void SetDiffuse(glm::vec3 v3);
	void SetDiffuse(glm::vec2 v2, float z);
	void SetDiffuse(float x, float y, float z);

public:

	void SetSpecular(glm::vec3 v3);
	void SetSpecular(glm::vec2 v2, float z);
	void SetSpecular(float x, float y, float z);

public:

	void SetShine(float shininess);

private:

	glm::vec3 v3_ambient;
	glm::vec3 v3_diffuse;
	glm::vec3 v3_specular;

private:

	float m_shininess;
};

#endif
