#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm.hpp>
#include <string>
#include "Component.h"

enum Materials
{
	M_AMBIENT = 0, M_SPECULAR, M_DIFFUSE, M_SHINE
};	
class Material: public Component
{
public:

	Material();
	~Material();

public:

	void SendData(Materials m, std::string shader);

public:

	glm::vec3 GetAmbient() const;
	glm::vec3 GetDiffuse() const;
	glm::vec3 GetSpecular() const;

public:

	void SetAmbient(glm::vec3 v3);
	void SetDiffuse(glm::vec3 v3);
	void SetSpecular(glm::vec3 v3);

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
