#include "Material.h"
#include "TheShader.h"
#include "TheDebug.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Material::Material()
{
	m_name = "Material";
	m_shininess = 0;
	v3_ambient = glm::vec3(1.0f);
	v3_diffuse = glm::vec3(1.0f);
	v3_specular = glm::vec3(1.0f);
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Material::~Material()
{
}

//-------------------------------------------------------------------------------
//Send Data
//-------------------------------------------------------------------------------
void Material::SendData(Materials m, std::string shader)
{
	std::string tempString;

	switch (m)
	{
	case M_AMBIENT:

		tempString = shader + "_material.ambient";
		TheShader::Instance()->SendUniformData(tempString.c_str(), v3_ambient);
										
		break;							
										
	case M_SPECULAR:					
		
		tempString = shader + "_material.diffuse";
		TheShader::Instance()->SendUniformData(tempString.c_str(), v3_diffuse);
										
		break;							
										
	case M_DIFFUSE:						
					
		tempString = shader + "_material.specular";
		TheShader::Instance()->SendUniformData(tempString.c_str(), v3_specular);
							
		break;				
							
	case M_SHINE:			
							
		tempString = shader + "_material.shininess";
		TheShader::Instance()->SendUniformData(tempString.c_str(), m_shininess);
		
		break;

	default:

		break;
	}
}

//-------------------------------------------------------------------------------
//Set Ambient
//-------------------------------------------------------------------------------
void Material::SetAmbient(glm::vec3 v3)
{
	v3_ambient = v3;
}

void Material::SetAmbient(glm::vec2 v2, float z)
{
	v3_ambient = glm::vec3(v2, z);
}

void Material::SetAmbient(float x, float y, float z)
{
	v3_ambient = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Diffuse
//-------------------------------------------------------------------------------
void Material::SetDiffuse(glm::vec3 v3)
{
	v3_diffuse = v3;
}

void Material::SetDiffuse(glm::vec2 v2, float z)
{
	v3_diffuse = glm::vec3(v2, z);
}

void Material::SetDiffuse(float x, float y, float z)
{
	v3_diffuse = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Specular
//-------------------------------------------------------------------------------
void Material::SetSpecular(glm::vec3 v3)
{
	v3_specular = v3;
}

void Material::SetSpecular(glm::vec2 v2, float z)
{
	v3_specular = glm::vec3(v2, z);

}

void Material::SetSpecular(float x, float y, float z)
{
	v3_specular = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Shine
//-------------------------------------------------------------------------------
void Material::SetShine(float shininess)
{
	m_shininess = shininess;
}
