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
//Get Ambient
//-------------------------------------------------------------------------------
glm::vec3 Material::GetAmbient() const
{
	return glm::vec3();
}

//-------------------------------------------------------------------------------
//Get Diffuse
//-------------------------------------------------------------------------------
glm::vec3 Material::GetDiffuse() const
{
	return glm::vec3();
}

//-------------------------------------------------------------------------------
//Get Specular
//-------------------------------------------------------------------------------
glm::vec3 Material::GetSpecular() const
{
	return glm::vec3();
}

//-------------------------------------------------------------------------------
//Set Ambient
//-------------------------------------------------------------------------------
void Material::SetAmbient(glm::vec3 v3)
{
	v3_ambient = v3;
}

//-------------------------------------------------------------------------------
//Set Diffuse
//-------------------------------------------------------------------------------
void Material::SetDiffuse(glm::vec3 v3)
{
	v3_diffuse = v3;
}

//-------------------------------------------------------------------------------
//Set Specular
//-------------------------------------------------------------------------------
void Material::SetSpecular(glm::vec3 v3)
{
	v3_specular = v3;
}

//-------------------------------------------------------------------------------
//Set Shine
//-------------------------------------------------------------------------------
void Material::SetShine(float shininess)
{
	m_shininess = shininess;
}
