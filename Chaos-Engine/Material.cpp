#include "Material.h"
#include "TheShader.h"
#include "TheDebug.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Material::Material()
{
	name = "Material";
	shininess = 0;
	ambient = glm::vec3(1.0f);
	diffuse = glm::vec3(1.0f);
	specular = glm::vec3(1.0f);
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
		TheShader::Instance()->SendUniformData(tempString.c_str(), ambient);
										
		break;							
										
	case M_SPECULAR:					
		
		tempString = shader + "_material.diffuse";
		TheShader::Instance()->SendUniformData(tempString.c_str(), diffuse);
										
		break;							
										
	case M_DIFFUSE:						
					
		tempString = shader + "_material.specular";
		TheShader::Instance()->SendUniformData(tempString.c_str(), specular);
							
		break;				
							
	case M_SHINE:			
							
		tempString = shader + "_material.shininess";
		TheShader::Instance()->SendUniformData(tempString.c_str(), shininess);
		
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
	return ambient;
}

//-------------------------------------------------------------------------------
//Get Diffuse
//-------------------------------------------------------------------------------
glm::vec3 Material::GetDiffuse() const
{
	return diffuse;
}

//-------------------------------------------------------------------------------
//Get Specular
//-------------------------------------------------------------------------------
glm::vec3 Material::GetSpecular() const
{
	return specular;
}

//-------------------------------------------------------------------------------
//Set Ambient
//-------------------------------------------------------------------------------
void Material::SetAmbient(glm::vec3 v3)
{
	ambient = v3;
}

//-------------------------------------------------------------------------------
//Set Diffuse
//-------------------------------------------------------------------------------
void Material::SetDiffuse(glm::vec3 v3)
{
	diffuse = v3;
}

//-------------------------------------------------------------------------------
//Set Specular
//-------------------------------------------------------------------------------
void Material::SetSpecular(glm::vec3 v3)
{
	specular = v3;
}

//-------------------------------------------------------------------------------
//Set Shine
//-------------------------------------------------------------------------------
void Material::SetShine(float shininess)
{
	shininess = shininess;
}
