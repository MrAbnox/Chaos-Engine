#include "Light.h"
#include "TheShader.h"
#include <string>
#include "Tools.h"
#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "TheInput.h"


int Light::s_numberSpotLights; 
int Light::s_numberPointLights;
int Light::s_directionalLightNumber;

bool Light::s_hasReadConfigFile;

std::map<std::string, float> Light::s_lightValues;
 
Light::Light(const Lights light)
{
	glGenVertexArrays(1, &m_VAO);
	if (!s_hasReadConfigFile == true)
	{
		OpenConfigurations();
	}

	v3_rgb = glm::vec3(0.0f);
	v3_ambient = glm::vec3(0.0f);
	v3_diffuse = glm::vec3(0.0f);
	v3_specular = glm::vec3(0.0f);
	v3_position = glm::vec3(0.0f);
	v3_direction = glm::vec3(0.0f);

	m_linear = 0.0f;
	m_cutOff = 0.0f;
	m_constant = 0.0f;
	m_quadratic = 0.0f;
	m_outerCutOff = 0.0f;

	m_light = light;
	


	Reset();
}

//-------------------------------------------------------------------------------
//Create
//-------------------------------------------------------------------------------
void Light::Create()
{
	m_shadowInfo = new ShadowInfo(glm::ortho(-40, 40, -40, 40, -40, 40));
	GLuint VBO_color;
	GLint m_colorAttributeID = TheShader::Instance()->GetAttributeID("Lightless_colorIn");

	glm::vec3 m_color = v3_ambient;

	GLfloat color[] = { m_color.r, m_color.g, m_color.b,
							m_color.r, m_color.g, m_color.b };

	glGenBuffers(1, &VBO_color);

	glBindVertexArray(m_VAO);
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

	KeyState keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_J])
	{
		v3_position += glm::vec3(0.01f, 0.0f, 0.0f);
	}
	else if (keys[SDL_SCANCODE_L])
	{
		v3_position += glm::vec3(-0.01f, 0.0f, 0.0f);
	}
	else if (keys[SDL_SCANCODE_I])
	{
		v3_position += glm::vec3(0.0f, 0.01f, 0.00f);
	}
	else if (keys[SDL_SCANCODE_K])
	{
		v3_position += glm::vec3(0.0f, -0.01f, -0.01f);
	}
	else if (keys[SDL_SCANCODE_0])
	{
		v3_position += glm::vec3(0.0f, 0.0f, 0.01f);
	}
	else if (keys[SDL_SCANCODE_9])
	{
		v3_position += glm::vec3(0.0f, 0.0f, -0.01f);
	}
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void Light::Draw()
{
	if (m_light == POINTLIGHT)
	{
		glPointSize(m_pointSize);

		glBindVertexArray(m_VAO);
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

	switch (m_light)
	{
	case SPOTLIGHT:

		//--------------------------------------------
		//Define Variables
		//--------------------------------------------

		//============================================

		//Set name
		m_name = "SpotLight";

		//Add one SpotLight
		s_numberSpotLights++;

		//send info to the shaders
		TheShader::Instance()->SendUniformData("Lighting_numberSpotLights", s_numberSpotLights);

		//tempString
		tempString = "Spot_";

		v3_direction.x = s_lightValues["Spot_direction.x"];
		v3_direction.y = s_lightValues["Spot_direction.y"];
		v3_direction.z = s_lightValues["Spot_direction.z"];

		//CutOff
		m_cutOff = s_lightValues["Spot_cutOff"];
		//OuterCutOff 
		m_outerCutOff = s_lightValues["Spot_outerCutOff"];

		break;

	case POINTLIGHT:

		//Set name
		m_name = "PointLight";

		//tempString
		tempString = "Point_";

		//Set Light Number
		m_lightNumber = s_numberPointLights;

		//Add one
		s_numberPointLights++;

		//send info to the shaders
		TheShader::Instance()->SendUniformData("Lighting_numberPointLights", s_numberPointLights);

		//Point size
		m_pointSize = 50.0f;

		v3_position = glm::vec3(0.7f, 2.2f, 2.0f);

		break;

	case DIRECTIONALLIGHT:
		
		//Set name
		m_name = "DirectionalLight";

		tempString = "directional_";

		//Send directional light


		if (s_directionalLightNumber < 1)
		{
			s_directionalLightNumber++;

			//Direction
			v3_direction.x = s_lightValues["Directional_direction.x"];
			v3_direction.y = s_lightValues["Directional_direction.y"];
			v3_direction.z = s_lightValues["Directional_direction.z"];
		}
		else
		{
			delete this;
		}

		TheShader::Instance()->SendUniformData("Lighting_isDirectionalLight", s_directionalLightNumber);
		break;
	}
	//cube color
	v3_rgb.x = s_lightValues[tempString + "rgb.x"];
	v3_rgb.y = s_lightValues[tempString + "rgb.y"];
	v3_rgb.z = s_lightValues[tempString + "rgb.z"];

	//ambient
	v3_ambient.x = s_lightValues[tempString + "ambient.x"];
	v3_ambient.y = s_lightValues[tempString + "ambient.y"];
	v3_ambient.z = s_lightValues[tempString + "ambient.z"];

	//diffuse
	v3_diffuse.x = s_lightValues[tempString + "diffuse.x"];
	v3_diffuse.y = s_lightValues[tempString + "diffuse.y"];
	v3_diffuse.z = s_lightValues[tempString + "diffuse.z"];

	//specular
	v3_specular.x = s_lightValues[tempString + "specular.x"];
	v3_specular.y = s_lightValues[tempString + "specular.y"];
	v3_specular.z = s_lightValues[tempString + "specular.z"];

	//Linear
	m_linear = s_lightValues[tempString + "linear"];
	//Constant
	m_constant = s_lightValues[tempString + "constant"];
	//Quadratic
	m_quadratic = s_lightValues[tempString + "quadratic"];

	//position
	v3_position.x = s_lightValues["position.x"];
	v3_position.y = s_lightValues["position.y"];
	v3_position.z = s_lightValues["position.z"];

	m_pointSize = s_lightValues["pointSize"];
}

//-------------------------------------------------------------------------------
//Send info to shaders
//-------------------------------------------------------------------------------
void Light::SendInfo()
{
	switch (m_light)
	{
	case SPOTLIGHT:

		TheShader::Instance()->SendUniformData("Lighting_spotLight.position", v3_position);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.direction", v3_direction);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.ambient", v3_ambient);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.diffuse", v3_diffuse);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.specular", v3_specular);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.constant", m_constant);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.linear", m_linear);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.quadratic", m_quadratic);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.cutOff", glm::cos(glm::radians(m_cutOff)));
		TheShader::Instance()->SendUniformData("Lighting_spotLight.outerCutOff", glm::cos(glm::radians(m_outerCutOff)));

		TheShader::Instance()->SendUniformData("LightMap_light.position", v3_position);
		TheShader::Instance()->SendUniformData("LightMap_light.ambient", v3_ambient);
		TheShader::Instance()->SendUniformData("LightMap_light.diffuse", v3_diffuse);
		TheShader::Instance()->SendUniformData("LightMap_light.specular", v3_specular);

		TheShader::Instance()->SendUniformData("Toon_light.position", v3_position);
		TheShader::Instance()->SendUniformData("Toon_light.intensity", glm::vec3(1.0f));

		break;

	case POINTLIGHT:

		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].position", v3_position);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].ambient", v3_ambient);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].diffuse", v3_diffuse);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].specular", v3_specular);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].constant", m_constant);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].linear", m_linear);
		TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].quadratic", m_quadratic);

		break;

	case DIRECTIONALLIGHT:

		TheShader::Instance()->SendUniformData("Lighting_dirLight.direction", v3_direction);
		TheShader::Instance()->SendUniformData("Lighting_dirLight.ambient", v3_ambient);
		TheShader::Instance()->SendUniformData("Lighting_dirLight.diffuse", v3_diffuse);
		TheShader::Instance()->SendUniformData("Lighting_dirLight.specular", v3_specular);

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
			ParseText(textString, token, s_lightValues);
		}
		s_hasReadConfigFile = true;
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

//-------------------------------------------------------------------------------
//Set Camera Pos
//-------------------------------------------------------------------------------
void Light::SetPos(const glm::vec3 v3)
{
	v3_position = v3;
}

void Light::SetPos(const float x, const float y, const float z)
{
	v3_position = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Camera forward
//-------------------------------------------------------------------------------
void Light::SetDirection(const glm::vec3 v3)
{
	if (!m_light == POINTLIGHT)
	{
		v3_direction = v3;
	}
	else
	{
		TheDebug::Log("Trying to Set direction on Point lights who do not have a direction", WARNING);
	}
}

void Light::SetDirection(const float x, const float y, const float z)
{
	if (!m_light == POINTLIGHT)
	{
		v3_direction = glm::vec3(x, y, z);
	}
	else
	{
		TheDebug::Log("Trying to Set direction on Point lights who do not have a direction", WARNING);
	}
}

//-------------------------------------------------------------------------------
//Get Shadow Info
//-------------------------------------------------------------------------------
ShadowInfo* Light::GetShadowInfo()
{
	return m_shadowInfo;
}
//-------------------------------------------------------------------------------
//Set Shadow Info
//-------------------------------------------------------------------------------
void Light::SetShadowInfo(ShadowInfo* shadowinfo)
{
	if (m_shadowInfo)
	{
		delete m_shadowInfo;
	}

	m_shadowInfo = shadowinfo;
}



