#include "DirectionalLight.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
DirectionalLight::DirectionalLight()
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

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
DirectionalLight::~DirectionalLight()
{
}

//-------------------------------------------------------------------------------
//OnEnter function
//-------------------------------------------------------------------------------
void DirectionalLight::Create()
{
	m_box->Create();
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void DirectionalLight::Update()
{
	TheShader::Instance()->SendUniformData("Lighting_dirLight.direction", v3_direction);
	TheShader::Instance()->SendUniformData("Lighting_dirLight.ambient", v3_ambient);
	TheShader::Instance()->SendUniformData("Lighting_dirLight.diffuse", v3_diffuse);
	TheShader::Instance()->SendUniformData("Lighting_dirLight.specular", v3_specular);

	m_box->Update();
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void DirectionalLight::Draw()
{
	m_box->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void DirectionalLight::Destroy()
{
}
