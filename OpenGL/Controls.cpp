#include "Controls.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Controls::Controls()
{
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Controls::~Controls()
{
	delete m_quad;
}

//-------------------------------------------------------------------------------
//On Enter
//-------------------------------------------------------------------------------
void Controls::OnEnter()
{
	
	v3_rgb = glm::vec3(1.0f);
	std::string tempString = "./Sprites/Controls.jpg";
	m_quad = new Quad(v3_rgb, tempString, "Controls");
	m_quad->SetIsLit(0);
	m_quad->Create("Lightless");
	
	m_quad->Scale(300.0f, 300.0f, 0.0f);
	m_quad->Translate(glm::vec3(1.0f, 3.0f, 0.0f));
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void Controls::Update()
{
	m_quad->Update();
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void Controls::Draw()
{
	m_quad->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Controls::Destroy()
{
	m_quad->Destroy();
}