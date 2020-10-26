#include "Box.h"
#include "Cube.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Box::Box(boxes b, glm::vec3 position)
{
	//Create temp string for filePath
	std::string tempFilePath;
	std::string tempFilePath2;

	//Create Temp vector
	std::vector<std::string> faces;

	//Create Type
	boxType_ = b;

	//Check what type of texture to assign
	switch (boxType_)
	{
	case CRATE:

		//Set name
		name = "Crate";

		//Set cube not mapped
		isMapped = false;

		//Set a crate texture
		tempFilePath = "Textures/Crate/Crate_2_Diffuse.png";

		//Set Shader
		shader = "ShadowMapping";

		//Create Cube
		primitive = new Cube(isMapped, tempFilePath, "Crate");

		break;

	case LAMP:

		//Set name
		name = "Lamp";

		//Set cube not mapped
		isMapped = false;

		//Set redstone Lamp texture
		tempFilePath = "Textures/Box/redstone.png";

		//Create Cube
		primitive = new Cube(isMapped, tempFilePath, "Lamp");


		break;

	case BLANK:

		//Set name
		name = "Box";

		//Set cube not mapped
		isMapped = false;

		//Set Shader
		shader = "Lightless";

		//Create Cube
		primitive = new Cube(shader);

		break;

	case STEELCRATE:

		//Set name
		name = "SteelCrate";

		//Set cube to not mapped;
		isMapped = false;

		//Create Cube
		tempFilePath = "Textures/Crate/Crate_Steel.png";

		tempFilePath2 = "Textures/Crate/Crate_Steel_Specular.png";

		//Set Shader
		shader = "LightMap";

		//Create Cube
		primitive = new Cube(tempFilePath, tempFilePath2, "SteelCrate", "SteelCrateBorder");

		break;

	case C_SKYBOX:

		//Set name
		name = "Skybox";

		//Set Skybox size
		size = glm::vec3(1000.0f, 1000.0f, 1000.0f);

		//Set is Mapped to true
		isMapped = true;

		faces.push_back("Textures/SkyBox/SkyBoxFaces/right.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/left.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/top.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/bottom.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/front.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/back.jpg");

		//Set Shader
		shader = "Skybox";

		//Create Cube Map
		primitive = new Cube(faces, "CubeSkyBox");

		//Scale Skybox
		primitive->Scale(size);

		break;

	case SIMPLE:

		AddComponent(MATERIAL);

		//Set Object's name
		name = "DefaultBox";

		//Set cube not mapped
		isMapped = false;

		//Set Shader
		shader = "Lighting";

		//Create Cube
		primitive = new Cube(shader);


		break;

	case GLASS:

		shader = "Cubemap";

		//Set cube mapped
		isMapped = true;

		//Create Glass cube
		primitive = new Cube(shader);

		break;

	default:

		break;
	}

	if (primitive->GetMaterial() != nullptr)
	{
		material = primitive->GetMaterial();
	}

	//Set transform to primitive's object
	transform = primitive->GetTransform();

	//Translate to Initial Position
	primitive->Translate(position);
}

//-------------------------------------------------------------------------------
//Destructor 
//-------------------------------------------------------------------------------
Box::~Box()
{
	Destroy();
}

//-------------------------------------------------------------------------------
//OnEnter function
//-------------------------------------------------------------------------------
void Box::Create()
{
	//OnEnter
	primitive->Create(shader);
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void Box::Update()
{
	primitive->SetShader(shader);
	primitive->Update();
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void Box::Draw()
{
	primitive->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Box::Destroy()
{
	delete primitive;
}
