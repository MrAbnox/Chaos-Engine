#include "PointLight.h"
#include "TheShader.h"
#include "TheInput.h"


//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
PointLight::PointLight(glm::vec3 position, int lightNumber, int lightColor)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	//Set Light Number
	m_lightNumber = lightNumber;

	//Cube color
	v3_rgb = glm::vec3(1.0f, 0.0f, 0.0f);

	glm::vec3 pointLightColors[] = 
	{
		glm::vec3(1.0f, 0.6f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0, 0.0f),
		glm::vec3(0.2f, 0.2f, 1.0f)
	};

	//Point size
	m_pointSize = 50.0f;

	//Position
	v3_position = position;

	//Ambient
	v3_ambient = glm::vec3(pointLightColors[lightColor].x * 0.1f, pointLightColors[lightColor].y * 0.1f, pointLightColors[lightColor].z * 0.1f);

	//Diffuse
	v3_diffuse = glm::vec3(pointLightColors[lightColor].x, pointLightColors[lightColor].y, pointLightColors[lightColor].z);

	//Specular
	v3_specular = glm::vec3(pointLightColors[lightColor].x, pointLightColors[lightColor].y, pointLightColors[lightColor].z);

	//Constant
	m_constant = 1.0f;

	//Linear
	m_linear = 0.09f;

	//Quadratic
	m_quadratic = 0.032f;
		
	//============================================

	//Create box as a Lamp
	m_box = new Box(BLANK, v3_rgb, glm::vec3(v3_position.x, v3_position.y, v3_position.z));

	m_box->Scale(glm::vec3(0.20f));
}

//-------------------------------------------------------------------------------
//Destructor 
//-------------------------------------------------------------------------------
PointLight::~PointLight()
{
}

//-------------------------------------------------------------------------------
//OnEnter function
//-------------------------------------------------------------------------------
void PointLight::Create()
{
	m_box->Create();
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void PointLight::Update()
{
	TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].position", v3_position);
	TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].ambient", v3_ambient);
	TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].diffuse", v3_diffuse);
	TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].specular", v3_specular);
	TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].constant", m_constant);
	TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].linear", m_linear);
	TheShader::Instance()->SendUniformData("Lighting_pointLights[" + std::to_string(m_lightNumber) + "].quadratic", m_quadratic);

	KeyState keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_L])
	{
		m_box->Translate(glm::vec3(0.01f, 0.0f, 0.0f));
		v3_position += glm::vec3(0.01, 0.0f, 0.0f);
	}
	else if (keys[SDL_SCANCODE_K])
	{
		m_box->Translate(glm::vec3(-0.01f, 0.0f, 0.0f));
		v3_position += glm::vec3(-0.01, 0.0f, 0.0f);
	}
	else if (keys[SDL_SCANCODE_O])
	{
		m_box->Translate(glm::vec3(0.0f, 0.0f, 0.01f));
		v3_position += glm::vec3(0.0, 0.0f, 0.01f);
	}
	else if (keys[SDL_SCANCODE_M])
	{
		m_box->Translate(glm::vec3(0.0f, 0.0f, -0.01f));
		v3_position += glm::vec3(0.0f, 0.0f, -0.01f);
	}
	else if (keys[SDL_SCANCODE_0])
	{
		m_box->Translate(glm::vec3(0.0f, 0.01f, 0.0f));
		v3_position += glm::vec3(0.0f, 0.01f, 0.0f);
	}
	else if (keys[SDL_SCANCODE_1])
	{
		m_box->Translate(glm::vec3(0.0f, -0.01f, 0.0f));
		v3_position += glm::vec3(0.01, -0.01f, 0.0f);
	}

	m_box->Update();
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void PointLight::Draw()
{
	m_box->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void PointLight::Destroy()
{
	delete m_box;
}
