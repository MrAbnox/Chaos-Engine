#include "SpotLight.h"
#include "TheShader.h"
#include "TheInput.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
SpotLight::SpotLight(glm::vec3 initialposition)
{

	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	//cube color
	v3_rgb = glm::vec3(1.0f);

	//point size
	m_pointSize = 50.0f;

	//position
	v3_position = initialposition;

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
	m_box = new Box(LAMP, v3_rgb, glm::vec3(initialposition.x, initialposition.y, initialposition.z));

	m_box->Scale(glm::vec3(0.20f));
}

//-------------------------------------------------------------------------------
//Destructor 
//-------------------------------------------------------------------------------
SpotLight::~SpotLight()
{
	Destroy();
}

//-------------------------------------------------------------------------------
//OnEnter function
//-------------------------------------------------------------------------------
void SpotLight::Create()
{
	m_box->Create();
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void SpotLight::Update(glm::vec3 cameraposition, glm::vec3 camerafront)
{
	//----------------------------- Send light information to light shader

	TheShader::Instance()->SendUniformData("Lighting_spotLight.position", cameraposition);
	TheShader::Instance()->SendUniformData("Lighting_spotLight.direction", camerafront);
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


	KeyState keys = TheInput::Instance()->GetKeyStates();
	//Update box
	m_box->Update();
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void SpotLight::Draw()
{
	m_box->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void SpotLight::Destroy()
{
	delete m_box;
}
