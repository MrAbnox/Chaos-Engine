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
	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
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
		TheShader::Instance()->SendUniformData(tempString.c_str(), m_ambient);
										
		break;							
										
	case M_SPECULAR:					
		
		tempString = shader + "_material.diffuse";
		TheShader::Instance()->SendUniformData(tempString.c_str(), m_diffuse);
										
		break;							
										
	case M_DIFFUSE:						
					
		tempString = shader + "_material.specular";
		TheShader::Instance()->SendUniformData(tempString.c_str(), m_specular);
							
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
//Get Ambient
//-------------------------------------------------------------------------------
glm::vec3 Material::GetAmbient() const
{
	return m_ambient;
}

//-------------------------------------------------------------------------------
//Get Diffuse
//-------------------------------------------------------------------------------
glm::vec3 Material::GetDiffuse() const
{
	return m_diffuse;
}

//-------------------------------------------------------------------------------
//Get Specular
//-------------------------------------------------------------------------------
glm::vec3 Material::GetSpecular() const
{
	return m_specular;
}

//-------------------------------------------------------------------------------
//Set Ambient
//-------------------------------------------------------------------------------
void Material::SetAmbient(glm::vec3 v3)
{
	m_ambient = v3;
}

//-------------------------------------------------------------------------------
//Set Diffuse
//-------------------------------------------------------------------------------
void Material::SetDiffuse(glm::vec3 v3)
{
	m_diffuse = v3;
}

//-------------------------------------------------------------------------------
//Set Specular
//-------------------------------------------------------------------------------
void Material::SetSpecular(glm::vec3 v3)
{
	m_specular = v3;
}

//-------------------------------------------------------------------------------
//Set Shine
//-------------------------------------------------------------------------------
void Material::SetShine(float shininess)
{
	m_shininess = shininess;
}
