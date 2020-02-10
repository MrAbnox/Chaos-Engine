#include "Light.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Set Ambient
//-------------------------------------------------------------------------------
void Light::SetAmbient(glm::vec3 v3)
{
	v3_ambient = v3;
}

void Light::SetAmbient(float x, float y, float z)
{
	v3_ambient = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Diffuse
//-------------------------------------------------------------------------------
void Light::SetDiffuse(glm::vec3 v3)
{
	v3_diffuse = v3;
}

void Light::SetDiffuse(float x, float y, float z)
{
	v3_diffuse = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Specular
//-------------------------------------------------------------------------------
void Light::SetSpecular(glm::vec3 v3)
{
	v3_specular = v3;
}

void Light::SetSpecular(float x, float y, float z)
{
	v3_specular = glm::vec3(x, y, z);
}


