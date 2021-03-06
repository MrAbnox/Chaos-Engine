#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm.hpp>
#include <string>
#include "Component.h"

enum class Materials
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

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

private:

	float shininess;
};

#endif
