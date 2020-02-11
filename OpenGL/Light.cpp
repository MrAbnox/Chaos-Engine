#include "Light.h"
#include "TheShader.h"
#include <string>
#include <iostream>


int Light::s_pointLightsNumber;
int Light::s_directionalLightNumber;
 
Light::Light(const Lights light)
{
	m_light = light;

	glm::vec3 test;
	switch (m_light)
	{
	case SPOTLIGHT:

	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

		//cube color
		v3_rgb = glm::vec3(1.0f);

		//point size
		m_pointSize = 50.0f;

		//position
		v3_position = glm::vec3(0.0f);

		//direction
		v3_direction = glm::vec3(-0.2, -1.0f, 0.3f);

		//ambient
		v3_ambient = glm::vec3(0.0f);

		//diffuse
		v3_diffuse = glm::vec3(1.0f);

		//specular
		v3_specular = glm::vec3(1.0f);

		//Constant
		m_constant = 1.0f;

		//Linear
		m_linear = 0.09f;

		//Quadratic
		m_quadratic = 0.032f;

		//CutOff
		m_cutOff = 10.0f;

		//OuterCutOff
		m_outerCutOff = 12.5f;

		//============================================

		//Create box as a Lamp
		m_box = new Box(LAMP, v3_rgb, glm::vec3(v3_position.x, v3_position.y, v3_position.z));

		m_box->Scale(glm::vec3(0.20f));

		break;

	case POINTLIGHT:

		//Set Light Number
		m_lightNumber = s_pointLightsNumber;

		//Add one
		s_pointLightsNumber++;

		//send info to the shaders
		TheShader::Instance()->SendUniformData("Lighting_pointLightsNumber", s_pointLightsNumber);

		//Cube color
		v3_rgb = glm::vec3(1.0, 0.0f, 0.0f);

		//Point size
		m_pointSize = 50.0f;

		if (m_lightNumber == 0)
		{
			test = glm::vec3(1.0f, 0.6f, 0.0f);
			//Position
			v3_position = glm::vec3(0.7f, 2.2f, 2.0f);
			//Ambient
			v3_ambient = glm::vec3(test.x * 0.1f, test.y * 0.1f, test.z * 0.1f);
			//Diffuse
			v3_diffuse = glm::vec3(test.x, test.y, test.z);
			//Specular
			v3_specular = glm::vec3(test.x, test.y, test.z);
		}
		else if (m_lightNumber == 1)
		{
			test = glm::vec3(1.0f, 0.0f, 0.0f);
			//Position
			v3_position = glm::vec3(2.3f, 5.3f, -4.0f);
			//Ambient
			v3_ambient = glm::vec3(test.x * 0.1f, test.y * 0.1f, test.z * 0.1f);
			//Diffuse
			v3_diffuse = glm::vec3(test.x, test.y, test.z);
			//Specular
			v3_specular = glm::vec3(test.x, test.y, test.z);
		}
		else if (m_lightNumber == 2)
		{
			test = glm::vec3(1.0f, 1.0, 0.0f);
			//Position
			v3_position = glm::vec3(-4.0f, 5.0f, -4.0f);
			//Ambient
			v3_ambient = glm::vec3(test.x * 0.1f, test.y * 0.1f, test.z * 0.1f);
			//Diffuse
			v3_diffuse = glm::vec3(test.x, test.y, test.z);
			//Specular
			v3_specular = glm::vec3(test.x, test.y, test.z);
		}
		else if (m_lightNumber == 3)
		{
			test = glm::vec3(0.2f, 0.2f, 1.0f);
			//Position
			v3_position = glm::vec3(0.0f, 5.0f, -3.0f);
			//Ambient
			v3_ambient = glm::vec3(test.x * 0.1f, test.y * 0.1f, test.z * 0.1f);
			//Diffuse
			v3_diffuse = glm::vec3(test.x, test.y, test.z);
			//Specular
			v3_specular = glm::vec3(test.x, test.y, test.z);
		}

		//Constant
		m_constant = 0.7f;

		//Linear
		m_linear = 0.05f;

		//Quadratic
		m_quadratic = 0.05f;

		//============================================

		//Create box as a Lamp
		m_box = new Box(LAMP, v3_rgb, glm::vec3(v3_position.x, v3_position.y, v3_position.z));

		m_box->Scale(glm::vec3(0.70f));

		break;

	case DIRECTIONALLIGHT:

		if (s_directionalLightNumber < 1)
		{


			s_directionalLightNumber++;

			//Cube color
			v3_rgb = glm::vec3(0.0f, 1.0f, 0.0f);

			//Point size
			m_pointSize = 50.0f;

			//Direction
			v3_direction = glm::vec3(-0.2f, -1.0f, -0.3f);

			//Ambient
			v3_ambient = glm::vec3(0.05f, 0.05f, 0.1f);

			//Diffuse
			v3_diffuse = glm::vec3(0.2f, 0.2f, 0.7);

			//Specular
			v3_specular = glm::vec3(0.7f, 0.7f, 0.7f);

			//Constant
			m_constant = 0.7f;

			//Linear
			m_linear = 0.05f;

			//Quadratic
			m_quadratic = 0.05f;

			//============================================
			//Create box as a Lamp

			m_box = new Box(BLANK, v3_rgb, glm::vec3(v3_position.x, v3_position.y, v3_position.z));

			m_box->Scale(glm::vec3(0.20f));
		}
		else
		{
			delete this;
		}
	}
}

//-------------------------------------------------------------------------------
//Create
//-------------------------------------------------------------------------------
void Light::Create()
{
	m_box->Create();

	if (m_light == DIRECTIONALLIGHT)
	{
		TheDebug::Log("TEST", DEBUG);
	}
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void Light::Update()
{
	switch (m_light)
	{
	case SPOTLIGHT:

		TheShader::Instance()->SendUniformData("Lighting_spotLight.position", v3_cameraPos);
		TheShader::Instance()->SendUniformData("Lighting_spotLight.direction", v3_cameraFront);
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

	m_box->Update();
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void Light::Draw()
{
	m_box->Draw();
}

//-------------------------------------------------------------------------------
//Destroy
//-------------------------------------------------------------------------------
void Light::Destroy()
{
	delete m_box;
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
void Light::SetCameraPos(const glm::vec3 v3)
{
	v3_cameraPos = v3;
}

void Light::SetCameraPos(const float x, const float y, const float z)
{
	v3_cameraPos = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Camera forward
//-------------------------------------------------------------------------------
void Light::SetCameraForward(const glm::vec3 v3)
{
	v3_cameraFront = v3;
}

void Light::SetCameraForward(const float x, const float y, const float z)
{
	v3_cameraFront = glm::vec3(x, y, z);
}


