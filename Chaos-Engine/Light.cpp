#include "Light.h"
#include "TheShader.h"
#include <string>
#include "Tools.h"
#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "TheInput.h"


int Light::numberSpotLights; 
int Light::numberPointLights;
int Light::directionalLightNumber;

bool Light::hasReadConfigFile;

std::map<std::string, float> Light::lightValues;
 
//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Light::Light(const Lights lightRef)
{
	glGenVertexArrays(1, &VAO);
	if (!hasReadConfigFile == true)
	{
		OpenConfigurations();
	}

	rgb = glm::vec3(0.0f);
	ambient = glm::vec3(0.0f);
	diffuse = glm::vec3(0.0f);
	specular = glm::vec3(0.0f);
	position = glm::vec3(0.0f);
	direction = glm::vec3(0.0f);

	linear = 0.0f;
	cutOff = 0.0f;
	constant = 0.0f;
	quadratic = 0.0f;
	outerCutOff = 0.0f;

	light = lightRef;
	
	Reset();
}

//-------------------------------------------------------------------------------
//Create
//-------------------------------------------------------------------------------
void Light::Create()
{
	shadowInfo = new ShadowInfo(glm::ortho(-40, 40, -40, 40, -40, 40));
	GLuint VBO_color;
	GLint m_colorAttributeID = TheShader::Instance()->GetAttributeID("Lightless_colorIn");

	glm::vec3 m_color = ambient;

	GLfloat color[] = { m_color.r, m_color.g, m_color.b,
							m_color.r, m_color.g, m_color.b };

	glGenBuffers(1, &VBO_color);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
	glVertexAttribPointer(m_colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_colorAttributeID);
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color , GL_STATIC_DRAW);
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void Light::Update()
{
	SendInfo();
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void Light::Draw()
{
	if (light == POINTLIGHT)
	{
		glPointSize(pointSize);

		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 1);

		glBindVertexArray(0);
	}
}

//-------------------------------------------------------------------------------
//Destroy
//-------------------------------------------------------------------------------
void Light::Destroy()
{
}

//-------------------------------------------------------------------------------
//Reset Variables to default
//-------------------------------------------------------------------------------
void Light::Reset()
{
	std::string tempString = "";

	switch (light)
	{
	case SPOTLIGHT:

		//Set name
		name = "SpotLight";

		//Add one SpotLight
		numberSpotLights++;

		//send info to the shaders
		TheShader::Instance()->SendUniformData("Lighting_numberSpotLights", numberSpotLights);

		//tempString
		tempString = "Spot_";

		direction.x = lightValues["Spot_direction.x"];
		direction.y = lightValues["Spot_direction.y"];
		direction.z = lightValues["Spot_direction.z"];

		//CutOff
		cutOff = lightValues["Spot_cutOff"];

		//OuterCutOff 
		outerCutOff = lightValues["Spot_outerCutOff"];

		break;

	case POINTLIGHT:

		//Set name
		name = "PointLight";

		//tempString
		tempString = "Point_";

		//Set Light Number
		lightNumber = numberPointLights;

		//Add one
		numberPointLights++;

		//send info to the shaders
		TheShader::Instance()->SendUniformData("Lighting_numberPointLights", numberPointLights);

		//Point size
		pointSize = 50.0f;

		position = glm::vec3(0.7f, 2.2f, 2.0f);

		break;

	case DIRECTIONALLIGHT:
		
		//Set name
		name = "DirectionalLight";

		tempString = "directional_";

		//Send directional light


		if (directionalLightNumber < 1)
		{
			directionalLightNumber++;

			direction.x = lightValues["Directional_direction.x"];
			direction.y = lightValues["Directional_direction.y"];
			direction.z = lightValues["Directional_direction.z"];
		}
		else
		{
			delete this;
		}

		TheShader::Instance()->SendUniformData("Lighting_isDirectionalLight", directionalLightNumber);
		break;
	}

	//cube color
	rgb.x = lightValues[tempString + "rgb.x"];
	rgb.y = lightValues[tempString + "rgb.y"];
	rgb.z = lightValues[tempString + "rgb.z"];

	//ambient
	ambient.x = lightValues[tempString + "ambient.x"];
	ambient.y = lightValues[tempString + "ambient.y"];
	ambient.z = lightValues[tempString + "ambient.z"];

	//diffuse
	diffuse.x = lightValues[tempString + "diffuse.x"];
	diffuse.y = lightValues[tempString + "diffuse.y"];
	diffuse.z = lightValues[tempString + "diffuse.z"];

	//specular
	specular.x = lightValues[tempString + "specular.x"];
	specular.y = lightValues[tempString + "specular.y"];
	specular.z = lightValues[tempString + "specular.z"];

	//Linear
	linear = lightValues[tempString + "linear"];
	//Constant
	constant = lightValues[tempString + "constant"];
	//Quadratic
	quadratic = lightValues[tempString + "quadratic"];

	//position
	position.x = lightValues["position.x"];
	position.y = lightValues["position.y"];
	position.z = lightValues["position.z"];

	pointSize = lightValues["pointSize"];
}

//-------------------------------------------------------------------------------
//Send info to shaders
//-------------------------------------------------------------------------------
void Light::SendInfo()
{
	switch (light)
	{
	case SPOTLIGHT:

		TheShader::Instance()->SendUniformData("Lighting_spotLight.position", position);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.direction", direction);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.ambient", ambient);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.diffuse", diffuse);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.specular", specular);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.constant", constant);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.linear", linear);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.quadratic", quadratic);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.cutOff", glm::cos(glm::radians(cutOff)));
		TheShader::Instance()->SendUniformData("Lighting_spotLight.outerCutOff", glm::cos(glm::radians(outerCutOff)));

		TheShader::Instance()->SendUniformData("LightMap_light.position", position);
		TheShader::Instance()->SendUniformData("LightMap_light.ambient", ambient);
		TheShader::Instance()->SendUniformData("LightMap_light.diffuse", diffuse);
		TheShader::Instance()->SendUniformData("LightMap_light.specular", specular);

		TheShader::Instance()->SendUniformData("Toon_light.position", position);
		TheShader::Instance()->SendUniformData("Toon_light.intensity", glm::vec3(1.0f));

		break;

	case POINTLIGHT:

		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(lightNumber) + "].position", position);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(lightNumber) + "].ambient", ambient);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(lightNumber) + "].diffuse", diffuse);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(lightNumber) + "].specular", specular);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(lightNumber) + "].constant", constant);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(lightNumber) + "].linear", linear);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(lightNumber) + "].quadratic", quadratic);

		TheShader::Instance()->SendUniformData("Toon_light.position", position);
		TheShader::Instance()->SendUniformData("Toon_light.intensity", glm::vec3(1.0f));
		break;

	case DIRECTIONALLIGHT:

		TheShader::Instance()->SendUniformData("Lighting_dirLight.direction", direction);
		TheShader::Instance()->SendUniformData("Lighting_dirLight.ambient", ambient);
		TheShader::Instance()->SendUniformData("Lighting_dirLight.diffuse", diffuse);
		TheShader::Instance()->SendUniformData("Lighting_dirLight.specular", specular);

		TheShader::Instance()->SendUniformData("Toon_light.position", position);
		TheShader::Instance()->SendUniformData("Toon_light.intensity", glm::vec3(1.0f));

		break;

	default:

		break;
	}
}

//-------------------------------------------------------------------------------
//Open Light Configurations
//-------------------------------------------------------------------------------
void Light::OpenConfigurations()
{
	std::ifstream m_configTextFile;

	m_configTextFile.open("./Data/Objects/Lights.txt", std::ios_base::in);

	char token = '=';

	if (m_configTextFile.is_open())
	{
		//----------------------------- Loop until text file is fully read

		while (!m_configTextFile.eof())
		{
			//----------------------------- Create temporary string and store corresponsive line

			std::string textString;
			std::getline(m_configTextFile, textString);
			//Parse each line 
			ParseText(textString, token, lightValues);
		}

		hasReadConfigFile = true;
	}
	else
	{
		TheDebug::Log("Could not open config file", ALERT);
	}
}

//================================================================================================== Setters

//-------------------------------------------------------------------------------
//Set Ambient
//-------------------------------------------------------------------------------
void Light::SetAmbient(glm::vec3 v3)
{
	ambient = v3;
}

void Light::SetAmbient(float x, float y, float z)
{
	ambient = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Diffuse
//-------------------------------------------------------------------------------
void Light::SetDiffuse(glm::vec3 v3)
{
	diffuse = v3;
}

void Light::SetDiffuse(float x, float y, float z)
{
	diffuse = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Specular
//-------------------------------------------------------------------------------
void Light::SetSpecular(glm::vec3 v3)
{
	specular = v3;
}

void Light::SetSpecular(float x, float y, float z)
{
	specular = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Camera Pos
//-------------------------------------------------------------------------------
void Light::SetPos(const glm::vec3 v3)
{
	position = v3;
}

void Light::SetPos(const float x, const float y, const float z)
{
	position = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Camera forward
//-------------------------------------------------------------------------------
void Light::SetDirection(const glm::vec3 v3)
{
	if (!light == POINTLIGHT)
	{
		direction = v3;
	}
	else
	{
		TheDebug::Log("Trying to Set direction on Point lights who do not have a direction", WARNING);
	}
}

void Light::SetDirection(const float x, const float y, const float z)
{
	if (!light == POINTLIGHT)
	{
		direction = glm::vec3(x, y, z);
	}
	else
	{
		TheDebug::Log("Trying to Set direction on Point lights who do not have a direction", WARNING);
	}
}