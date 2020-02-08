
#include "TheScreen.h"
#include "TheShader.h"
#include "TheDebug.h"
#include "TheInput.h"
#include "Game.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Box.h"
#include "Wall.h"
#include "Room.h"
#include "Floor.h"
#include "RoomState.h"


#include <iostream>

//-------------------------------------------------------------------------------
//OnEnter function
//-------------------------------------------------------------------------------
void RoomState::Create()
{
	//----------------------------- Initialize Managers

	//----------------------------- Initialize Managers

	isRunning = true;

	TheScreen::Instance()->Initialize();
	TheInput::Instance()->Initialize();

	TheShader::Instance()->CreateShaders("Lightless.vert", "Lightless.frag");
	TheShader::Instance()->CreateShaders("LightMap.vert", "LightMap.frag");
	TheShader::Instance()->CreateShaders("Lighting.vert", "Lighting.frag");
	TheShader::Instance()->CreateShaders("Shadow_Mapping.vert", "Shadow_Mapping.frag");
	TheShader::Instance()->CreateShaders("Shadow_Mapping_Depth.vert", "Shadow_Mapping_Depth.frag");
	TheShader::Instance()->CreateShaders("Quad_Depth.vert", "Quad_Depth.frag");

	TheShader::Instance()->Initialize();

	//-------------------------------------- Create objects in the scene

	m_gameObjects.push_back(new Box(STEELCRATE, glm::vec3(1.0f), glm::vec3(0.1f, 2.5f, 1.0f)));

	m_spotLight = new SpotLight(glm::vec3(0.0f));
	m_gameObjects.push_back(new DirectionalLight);
	m_gameObjects.push_back(new PointLight(glm::vec3(0.7f, 5.2f, 2.0f), 0, 0));
	m_gameObjects.push_back(new PointLight(glm::vec3(2.3f, 5.3f, -4.0f), 1, 1));
	m_gameObjects.push_back(new PointLight(glm::vec3(-4.0f, 5.0f, -4.0f), 2, 2));
	m_gameObjects.push_back(new PointLight(glm::vec3(0.0f, 5.0f, -3.0f), 3, 3));

	m_gameObjects.push_back(new SkyBox);

	m_controls = new Controls();

	m_grid = new Grid();

	m_freeCamera = new FreeCamera();

	m_uiCamera = new UICamera();

	m_model.Create("Lighting");
	m_model.LoadModel("./Models/PC.obj");
	m_model.LoadTexture("./Textures/Models/Room_diffuse.jpg", "car");


	//-------------------------------------- initialize Object functions

	m_controls->OnEnter();

	m_freeCamera->SetPerspView();

	m_spotLight->Create();

	//m_model.Scale(glm::vec3(0.1f));

	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Create();
	};

	//----------------------------- Get programs IDs
}

//-------------------------------------------------------------------------------
//Update Function
//-------------------------------------------------------------------------------
void RoomState::Update()
{
	TheInput::Instance()->Update();
	m_freeCamera->Update();
	m_freeCamera->SetPerspView();


	if (TheInput::Instance()->GetIsXClicked())
	{
		Game::Instance()->ExitGame();
	}

	//----------------------------- Clear the buffer so the next iteration of data can be loaded in

	TheScreen::Instance()->Clear();

	m_model.Update();
	m_model.Draw();

	//Draw camera
	m_freeCamera->Draw();

	//Draw Grid
	m_grid->Draw();

	//Draw SpotLight
	m_spotLight->Draw();

	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update();
	};

	m_spotLight->Update(m_freeCamera->GetPosition(), m_freeCamera->GetForward());



	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Draw();
	};


	//m_model.Draw();

	m_uiCamera->Draw();
	m_uiCamera->SetOrthoView();
	m_controls->Draw();

	//----------------------------- Swap Buffers

	TheScreen::Instance()->SwapBuffer();

	//----------------------------- Check for OpenGL errors

	GLenum errorCode = glGetError();

	if (errorCode == GL_NO_ERROR)
	{
		//no errors
	}
	else if (errorCode == GL_INVALID_OPERATION)
	{
		std::cout << "Yikes! Please Reboot" << std::endl;
	}
}

//-------------------------------------------------------------------------------
//OnExit
//-------------------------------------------------------------------------------
void RoomState::OnExit()
{

}
