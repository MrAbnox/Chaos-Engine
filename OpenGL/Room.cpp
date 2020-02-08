#include "Room.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Room::Room()
{
	//------------------------------------------------------------- 
	//Create Pouffes
	//-------------------------------------------------------------

	//Pouffe1
	m_pouffe.Create("Lighting");
	m_pouffe.LoadModel("./Models/Pouffe.obj");
	//m_pouffe.LoadTexture("./Textures/Models/M_Pouffe_Base_Color_Grey.png", "Pouffe_Grey");
	m_pouffe.Scale(glm::vec3(0.1f));

	
	//Pouffe2
	m_pouffe2.Create("Lighting");
	m_pouffe2.LoadModel("./Models/Pouffe.obj");
	//m_pouffe2.LoadTexture("./Textures/Models/M_Pouffe_Base_Color_Grey.png", "Pouffe_Grey");
	m_pouffe2.Scale(glm::vec3(0.1f));

	//Pouffe3
	m_pouffe3.Create("Lighting");
	m_pouffe3.LoadModel("./Models/Pouffe.obj");
	//m_pouffe3.LoadTexture("./Textures/Models/M_Pouffe_Base_Color_Grey.png", "Pouffe_Grey");
	m_pouffe3.Scale(glm::vec3(0.1f));

	//Pouffe4
	m_pouffe4.Create("Lighting");
	m_pouffe4.LoadModel("./Models/Pouffe.obj");
	//m_pouffe4.LoadTexture("./Textures/Models/M_Pouffe_Base_Color.png", "Pouffe_Orange");
	m_pouffe4.Scale(glm::vec3(0.1f));

	//Pouffe5
	m_pouffe5.Create("Lighting");
	m_pouffe5.LoadModel("./Models/Pouffe.obj");
	//m_pouffe5.LoadTexture("./Textures/Models/M_Pouffe_Base_Color.png", "Pouffe_Orange");
	m_pouffe5.Scale(glm::vec3(0.1f));



}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Room::~Room()
{
}

//-------------------------------------------------------------------------------
//On Enter
//-------------------------------------------------------------------------------
void Room::Create()
{
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void Room::Update()
{
	m_pouffe.Update();
	m_pouffe2.Update();
	m_pouffe3.Update();
	m_pouffe4.Update();
	m_pouffe5.Update();
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void Room::Draw()
{
	m_pouffe.Draw();
	m_pouffe2.Draw();
	m_pouffe3.Draw();
	m_pouffe4.Draw();
	m_pouffe5.Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Room::Destroy()
{
}
