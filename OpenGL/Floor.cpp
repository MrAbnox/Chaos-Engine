#include "Floor.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Floor::Floor(TYPE t, glm::vec3 position)
{
	v3_rgb = glm::vec3(1.0f);

	std::string tempString;

	switch (t)
	{
	case GRASS:

		//Set texture's location
		tempString = "Textures/Grass/Grass-01.jpg";

		//Set color to default
		v3_rgb = glm::vec3(1.0f);

		//Create Quad
		m_primitive = new Quad(v3_rgb, tempString, "Grass");

		//Set what shader to use
		m_shader = "Lighting";

		break;

	case TILED:

		//Set texture's location
		tempString = "Textures/Floors/TileFloor_Diffuse.bmp";

		//Set color to default
		v3_rgb = glm::vec3(1.0f);

		//Create Quad
		m_primitive = new Quad(v3_rgb, tempString, "Tiles");

		//Set what shader to use
		m_shader = "Lighting";

		break;

	case WOOD:

		//Set texture's location
		tempString = "Textures/Floors/WoodFloor.jpg";

		//Set color to default
		v3_rgb = glm::vec3(1.0f);

		//Create Quad
		m_primitive = new Quad(v3_rgb, tempString, "Wood");

		//Set what shader to use
		m_shader = "Lighting";

		break;

	case STONE:

		//Set texture's location
		tempString = "Textures/Floors/TileFloor_Diffuse.bmp";

		//Set color to default
		v3_rgb = glm::vec3(1.0f);

		//Create Quad
		m_primitive = new Quad (v3_rgb, tempString, "Stone");

		//Set what shader to use
		m_shader = "Lighting";

		break;

	case EMPTY:

		//Create Quad
		m_primitive = new Quad(v3_rgb);

		//Set what shader to use
		m_shader = "Lightless";

		break;

	case WATER:

		//Create Quad
		m_primitive = new Quad(v3_rgb);

		//Set what shader to use
		m_shader = "WaterShader";

		break;

	default:

		break;
	}

	//Make wall be in the right position for default
	m_primitive->Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	m_primitive->Scale(glm::vec3(3.0f));
	m_primitive->Translate(glm::vec3(0.0f, -0.25f, -1.0f));
	m_primitive->Translate(position);
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