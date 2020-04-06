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

	//----------------------------- Check what type of texture to assign
	switch (boxType_)
	{
	case CRATE:

		//Set name
		m_name = "Crate";

		//Set cube not mapped
		isMapped = false;

		//Set a crate texture
		tempFilePath = "Textures/Crate/Crate_2_Diffuse.png";

		//Set Shader
		m_shader = "ShadowMapping";

		//Create Cube
		m_primitive = new Cube(isMapped, tempFilePath, "Crate", m_shader);

		break;

	case LAMP:

		//Set name
		m_name = "Lamp";

		//Set cube not mapped
		isMapped = false;

		//Set redstone Lamp texture
		tempFilePath = "Textures/Box/redstone.png";

		//Create Cube
		m_primitive = new Cube(isMapped, tempFilePath, "Lamp", m_shader);


		break;

	case BLANK:

		//Set name
		m_name = "Box";

		//Set cube not mapped
		isMapped = false;

		//Set Shader
		m_shader = "Lightless";

		//Create Cube
		m_primitive = new Cube(m_shader);

		break;

	case STEELCRATE:

		//Set name
		m_name = "SteelCrate";

		//Set cube to not mapped;
		isMapped = false;

		//Create Cube
		tempFilePath = "Textures/Crate/Crate_Steel.png";

		tempFilePath2 = "Textures/Crate/Crate_Steel_Specular.png";

		//Set Shader
		m_shader = "LightMap";

		//Create Cube
		m_primitive = new Cube(tempFilePath, tempFilePath2, "SteelCrate", "SteelCrateBorder", m_shader);

		break;

	case C_SKYBOX:

		//Set name
		m_name = "Skybox";

		//Set Skybox size
		m_size = glm::vec3(1000.0f, 1000.0f, 1000.0f);

		//Set is Mapped to true
		isMapped = true;

		faces.push_back("Textures/SkyBox/SkyBoxFaces/right.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/left.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/top.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/bottom.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/front.jpg");
		faces.push_back("Textures/SkyBox/SkyBoxFaces/back.jpg");

		//Set Shader
		m_shader = "Skybox";

		//Create Cube Map
		m_primitive = new Cube(faces, "CubeSkyBox", m_shader);

		//Scale Skybox
		m_primitive->Scale(m_size);

		break;

	case SIMPLE:

		AddComponent(MATERIAL);

		//Set Object's name
		m_name = "DefaultBox";

		//Set cube not mapped
		isMapped = false;

		//Set Shader
		m_shader = "Lighting";

		//Create Cube
		m_primitive = new Cube(m_shader);


		break;

	case GLASS:

		m_shader = "Cubemap";

		//Set cube mapped
		isMapped = true;

		//Create Glass cube
		m_primitive = new Cube(m_shader);

		break;

	default:

		break;
	}

	if (m_primitive->GetMaterial() != nullptr)
	{
		m_material = m_primitive->GetMaterial();
	}
	//Set transform to primitive's object
	m_transform = m_primitive->GetTransform();

	//Translate to Initial Position
	m_primitive->Translate(position);
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
	m_primitive->Create(m_shader);
}

//-------------------------------------------------------------------------------
//Update function
//-------------------------------------------------------------------------------
void Box::Update()
{
	m_primitive->SetShader(m_shader);
	m_primitive->Update();

	/*if (m_shader == "Lighting")
	{
		KeyState keys = TheInput::Instance()->GetKeyStates(); 

		if (keys[SDL_SCANCODE_L])
		{
			Translate(glm::vec3(0.01f, 0.0f, 0.0f));
		}
		else if (keys[SDL_SCANCODE_K])
		{
			Translate(glm::vec3(-0.01f, 0.0f, 0.0f));
		}
		else if (keys[SDL_SCANCODE_O])
		{
			Translate(glm::vec3(0.0f, 0.0f, 0.01f));
		}
		else if (keys[SDL_SCANCODE_M])
		{
			Translate(glm::vec3(0.0f, 0.0f, -0.01f));
		}
		else if (keys[SDL_SCANCODE_0])
		{
			Translate(glm::vec3(0.0f, 0.01f, 0.0f));
		}
		else if (keys[SDL_SCANCODE_1])
		{
			Translate(glm::vec3(0.0f, -0.01f, 0.0f));
		}
	}*/
}

//-------------------------------------------------------------------------------
//Draw function
//-------------------------------------------------------------------------------
void Box::Draw()
{
	m_primitive->Draw();
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Box::Destroy()
{
	delete m_primitive;
}
