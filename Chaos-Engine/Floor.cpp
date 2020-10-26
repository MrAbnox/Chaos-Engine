#include "Floor.h"
#include "TheShader.h"
#include "TheInput.h"

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
		name = "Grass";

		//Set texture's location
		tempString = "Textures/Grass/Grass-01.jpg";

		//Create Quad
		primitive = new Quad(tempString, "Grass");

		//Set what shader to use
		shader = "Lighting";

		break;

	case TILED:

		//Set name
		name = "TiledFloor";

		//Set texture's location
		tempString = "Textures/Floors/TileFloor_Diffuse.bmp";

		//Create Quad
		primitive = new Quad(tempString, "Tiles");

		//Set what shader to use
		shader = "Lighting";

		break;

	case WOOD:

		//Set name
		name = "WoodFloor";

		//Set texture's location
		tempString = "Textures/WoodFloor.jpg";

		//Create Quad
		primitive = new Quad(tempString, "Wood");

		//Set what shader to use
		shader = "ShadowMapping";

		break;

	case STONE:

		//Set name
		name = "StoneFloor";

		//Set texture's location
		tempString = "Textures/Floors/TileFloor_Diffuse.bmp";

		//Create Quad
		primitive = new Quad (tempString, "Stone");

		//Set what shader to use
		shader = "Lighting";

		break;

	case EMPTY:

		//Set name
		name = "Floor";

		//Create Quad
		primitive = new Quad();

		//Set what shader to use
		shader = "Lightless";

		break;

	case WATER:

		//Set name
		name = "WaterFloor";

		//Create Quad
		primitive = new Quad();

		//Set what shader to use
		shader = "WaterShader";

		break;

	default:

		break;
	}

	//Assign object's transform to primitives
	transform = primitive->GetTransform();

	//Make wall be in the right position for default
	Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
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
	primitive->Create(shader);
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void Floor::Update()
{
	primitive->SetShader(shader);
	primitive->Update();

	KeyState keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_U])
	{
		Translate(glm::vec3(0.0f, 0.0f, 0.001f));
	}
	else if (keys[SDL_SCANCODE_O])
	{
		Translate(glm::vec3(0.0f, 0.0f, -0.001f));
	}
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void Floor::Draw()
{
	primitive->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Floor::Destroy()
{
}