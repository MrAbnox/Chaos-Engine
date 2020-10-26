#include "Wall.h"
#include "Quad.h"


//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Wall::Wall(WallType t , rotation r, glm::vec3 position)
{
	std::string tempString;

	name = "Wall";

	if (t == BRICKS)
	{
		name = "BrickWall";
		//Set texture path
		tempString = "Textures/bricks2.jpg";
	}
	else if (t == MIRROR)
	{
		name = "MirrorWall";
	primitive = new Quad(tempString, "Brick");
	}

	if (t == BRICKS)
	{
	//Create Quad
	primitive = new Quad(tempString, "Brick");

		primitive->SetNormalMap("Textures/bricks2_normal.jpg");
		primitive->SetHeightMap("Textures/bricks2_disp.jpg");
	}

	//Check what rotation will the wall use
	if (r == RIGHT)
	{
		primitive->Rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	//Assign object's transform to primitives
	transform = primitive->GetTransform();

	//Give intial transformations
	Scale(glm::vec3(3.0f));
	Translate(glm::vec3(0.0f, 0.5f, 0.0f));
	Translate(position);

	//Set Shader
	shader = "NormalMapping";
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Wall::~Wall()
{
	delete primitive;
	Destroy();
}

//-------------------------------------------------------------------------------
//On Enter
//-------------------------------------------------------------------------------
void Wall::Create()
{
	primitive->Create(shader);
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void Wall::Update()
{
	primitive->Update();
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void Wall::Draw()
{
	primitive->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Wall::Destroy()
{
	primitive->Destroy();
}
