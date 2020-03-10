#include "Floor.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Floor::Floor(TYPE t, glm::vec3 position)
{
	std::string tempString;

	switch (t)
	{
	case GRASS:

		//Set name
		m_name = "Grass";

		//Set texture's location
		tempString = "Textures/Grass/Grass-01.jpg";

		//Create Quad
		m_primitive = new Quad(tempString, "Grass");

		//Set what shader to use
		m_shader = "Lighting";

		break;

	case TILED:

		//Set name
		m_name = "TiledFloor";

		//Set texture's location
		tempString = "Textures/Floors/TileFloor_Diffuse.bmp";

		//Create Quad
		m_primitive = new Quad(tempString, "Tiles");

		//Set what shader to use
		m_shader = "Lighting";

		break;

	case WOOD:

		//Set name
		m_name = "WoodFloor";

		//Set texture's location
		tempString = "Textures/WoodFloor.jpg";

		//Create Quad
		m_primitive = new Quad(tempString, "Wood");

		//Set what shader to use
		m_shader = "ShadowMapping";

		break;

	case STONE:

		//Set name
		m_name = "StoneFloor";

		//Set texture's location
		tempString = "Textures/Floors/TileFloor_Diffuse.bmp";

		//Create Quad
		m_primitive = new Quad (tempString, "Stone");

		//Set what shader to use
		m_shader = "Lighting";

		break;

	case EMPTY:

		//Set name
		m_name = "Floor";

		//Create Quad
		m_primitive = new Quad();

		//Set what shader to use
		m_shader = "Lightless";

		break;

	case WATER:

		//Set name
		m_name = "WaterFloor";

		//Create Quad
		m_primitive = new Quad();

		//Set what shader to use
		m_shader = "WaterShader";

		break;

	default:

		break;
	}

	//Assign object's transform to primitives
	m_transform = m_primitive->GetTransform();

	//Make wall be in the right position for default
	Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	Scale(glm::vec3(3.0f));
	Translate(glm::vec3(0.0f, -0.25f, -1.0f));
	Translate(position);
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Floor::~Floor()
{
	Destroy();
}

//-------------------------------------------------------------------------------
//On Enter
//-------------------------------------------------------------------------------
void Floor::Create()
{
	m_primitive->Create(m_shader);
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void Floor::Update()
{
	m_primitive->SetShader(m_shader);
	m_primitive->Update();
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void Floor::Draw()
{
	m_primitive->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Floor::Destroy()
{
}