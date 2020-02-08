#include "Box.h"
#include "Cube.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Box::Box(boxes b, glm::vec3 rgb, glm::vec3 position)
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

		//Set cube not mapped
		isMapped = false;

		//Set color to white
		v3_rgb = glm::vec3(1.0f);

		//Set a crate texture
		tempFilePath = "Textures/Crate/Crate_2_Diffuse.png";

		//Create Cube
		m_primitive = new Cube(isMapped, v3_rgb, tempFilePath, "Crate");

		//Set Shader
		m_shader = "Lighting";


		break;

	case LAMP:

		//Set cube not mapped
		isMapped = false;

		//Set color to white
		v3_rgb = glm::vec3(1.0f);

		//Set redstone Lamp texture
		tempFilePath = "Textures/Box/redstone.png";

		//Set Shader
		m_shader = "Lightless";

		//Create Cube
		m_primitive = new Cube(isMapped, v3_rgb, tempFilePath, "Lamp");


		break;

	case BLANK:

		//Set cube not mapped
		isMapped = false;

		//Set color to an orange look alike
		v3_rgb = rgb;

		//Create Cube
		m_primitive = new Cube(v3_rgb);

		//Set Shader
		m_shader = "Lightless";

		break;

	case STEELCRATE:

		//Set cube to not mapped;
		isMapped = false;

		//Set color to look white
		v3_rgb = glm::vec3(1.0f);

		//Create Cube
		tempFilePath = "Textures/Crate/Crate_Steel.png";

		tempFilePath2 = "Textures/Crate/Crate_Steel_Specular.png";

		//Create Cube
		m_primitive = new Cube(v3_rgb, tempFilePath, tempFilePath2, "SteelCrate", "SteelCrateBorder");

		//Set Shader
		m_shader = "LightMap";

		break;

	case C_SKYBOX:

		//Set Skybox size
		m_size = glm::vec3(1000.0f, 1000.0f, 1000.0f);

		//Set is Mapped to true
		isMapped = true;

		//Set default color
		v3_rgb = glm::vec3(1.0f, 1.0f, 1.0f);

		faces.push_back("Textures/Skybox/right.jpg");
		faces.push_back("Textures/Skybox/left.jpg");
		faces.push_back("Textures/Skybox/top.jpg");
		faces.push_back("Textures/Skybox/bottom.jpg");
		faces.push_back("Textures/Skybox/front.jpg");
		faces.push_back("Textures/Skybox/back.jpg");

		//Create Cube Map
		m_primitive = new Cube(v3_rgb, faces, "CubeSkyBox");

		//Set Shader
		m_shader = "Lightless";

		//Scale Skybox
		m_primitive->Scale(m_size);

		break;

	default:

		break;
	}

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
