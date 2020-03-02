#include "SkyBox.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
SkyBox::SkyBox()
{
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
SkyBox::~SkyBox()
{
	Destroy();
}

//-------------------------------------------------------------------------------
//On Enter
//-------------------------------------------------------------------------------
void SkyBox::Create()
{
	//Set name
	m_name = "Skybox";

	v3_size = glm::vec3(1000.0f, 1000.0f, 1000.0f);

	bool isCubeMapped = true;
	box = new Cube(isCubeMapped, "Textures/Skybox/SkyBox_2.jpg", "SkyBox", "Lightless");

	box->Scale(v3_size);
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void SkyBox::Update()
{
	box->Update();
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void SkyBox::Draw()
{
	box->Draw();
}

//-------------------------------------------------------------------------------
//Destroy
//-------------------------------------------------------------------------------
void SkyBox::Destroy()
{
}
