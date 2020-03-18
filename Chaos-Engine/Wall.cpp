#include "Wall.h"
#include "Quad.h"


//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Wall::Wall(WallType t , rotation r, glm::vec3 position)
{
	std::string tempString;

	m_name = "Wall";

	if (t == BRICKS)
	{
		m_name = "BrickWall";
		//Set texture path
		tempString = "Textures/bricks2.jpg";
	}

	//Create Quad
	m_primitive = new Quad(tempString, "Brick");

	if (t == BRICKS)
	{
		m_primitive->SetNormalMap("Textures/bricks2_normal.jpg");
		m_primitive->SetHeightMap("Textures/bricks2_disp.jpg");
	}

	//Check what rotation will the wall use
	if (r == RIGHT)
	{
		m_primitive->Rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	//Assign object's transform to primitives
	m_transform = m_primitive->GetTransform();

	//Give intial transformations
	Scale(glm::vec3(3.0f));
	Translate(glm::vec3(0.0f, 0.5f, 0.0f));
	Translate(position);

	//Set Shader
	m_shader = "NormalMapping";
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Wall::~Wall()
{
	delete m_primitive;
	Destroy();
}

//-------------------------------------------------------------------------------
//On Enter
//-------------------------------------------------------------------------------
void Wall::Create()
{
	m_primitive->Create(m_shader);
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void Wall::Update()
{
	m_primitive->Update();
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void Wall::Draw()
{
	m_primitive->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Wall::Destroy()
{
	m_primitive->Destroy();
}
