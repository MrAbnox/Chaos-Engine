#include "TestState.h"
#include "TheDebug.h"
#include "Game.h"
#include "Box.h"
#include "Wall.h"
#include "Floor.h"
#include "TheShader.h"

#include <iostream>

//-------------------------------------------------------------------------------
//OnEnter function
//-------------------------------------------------------------------------------
void TestState::Create()
{
	//----------------------------- Initialize Managers

	isRunning = true;

	//-------------------------------------- Create objects in the scene

	m_spotLight = new Light(SPOTLIGHT);

	m_gameObjects.push_back(new Light(DIRECTIONALLIGHT));
	m_gameObjects.push_back(new Light(POINTLIGHT));
	m_gameObjects.push_back(new SkyBox);

	m_controls = new Controls();

	m_freeCamera = new FreeCamera();
	box = new Box(CRATE, glm::vec3(1.0f), glm::vec3(1.0f));
	m_uiCamera = new UICamera();
	  
	//------------------------------------------------
	//CREATE MODELS
	//------------------------------------------------

	m_table.Create("Lighting");
	m_table.LoadModel("./Models/Table.obj");
	m_table.LoadTexture("./Textures/Models/M_Table_Base_Color.png", "Table");
	m_table.Scale(glm::vec3(0.01f));

	m_pc.Create("Lighting");
	m_pc.LoadModel("./Models/PC.obj");
	m_pc.LoadTexture("./Textures/Models/M_PC_Base_Color.png", "PC");
	m_pc.Scale(glm::vec3(0.01f));

	m_ps4.Create("Lighting");
	m_ps4.LoadModel("./Models/PS4.obj");
	m_ps4.LoadTexture("./Textures/Models/M_PS4_Base_Color.png", "PS4");
	m_ps4.Scale(glm::vec3(0.01f));

	m_ps3.Create("Lighting");
	m_ps3.LoadModel("./Models/PS3.obj");
	m_ps3.LoadTexture("./Textures/Models/M_PS3_Base_Color.png", "PS3");
	m_ps3.Scale(glm::vec3(0.01f));

	m_sofa.Create("Lighting");
	m_sofa.LoadModel("./Models/Sofa.obj");
	m_sofa.LoadTexture("./Textures/Models/M_Sofa_Base_Color.png", "Sofa");
	m_sofa.Scale(glm::vec3(0.01f));

	m_wii.Create("Lighting");
	m_wii.LoadModel("./Models/Wii.obj");
	m_wii.LoadTexture("./Textures/Models/M_Wii_Base_Color.png", "Wii");
	m_wii.Scale(glm::vec3(0.01f));

	m_amp.Create("Lighting");
	m_amp.LoadModel("./Models/AMP.obj");
	m_amp.LoadTexture("./Textures/Models/M_Amp_Base_Color.png", "AMP");
	m_amp.Scale(glm::vec3(0.01f));

	m_pouffe.Create("Lighting");
	m_pouffe.LoadModel("./Models/Pouffe.obj");
	m_pouffe.LoadTexture("./Textures/Models/M_Pouffe_Base_Color.png", "Pouffe1");
	m_pouffe.Scale(glm::vec3(0.01f));

	m_subwoofer.Create("Lighting");
	m_subwoofer.LoadModel("./Models/Sub.obj");
	m_subwoofer.LoadTexture("./Textures/Models/M_Subwoofer_Base_Color.png", "Sub");
	m_subwoofer.Scale(glm::vec3(0.01f));

	m_tv.Create("Lighting");
	m_tv.LoadModel("./Models/TV.obj");
	m_tv.LoadTexture("./Textures/Models/M_TV_Base_Color.png", "TV");
	m_tv.Scale(glm::vec3(0.01f));

	m_aircon.Create("Lighting");
	m_aircon.LoadModel("./Models/AirCon.obj");
	m_aircon.LoadTexture("./Textures/Models/M_Air_conditioner_Base_Color.png", "AirCon");
	m_aircon.Scale(glm::vec3(0.01f));

	m_emergencyButton.Create("Lighting");
	m_emergencyButton.LoadModel("./Models/Emergency_button.obj");
	m_emergencyButton.LoadTexture("./Textures/Models/M_Emergency_button_Base_Color.png", "EmergencyButton");
	m_emergencyButton.Scale(glm::vec3(0.01f));

	m_exitButton.Create("Lighting");
	m_exitButton.LoadModel("./Models/Exit_button.obj");
	m_exitButton.LoadTexture("./Textures/Models/M_Exti_button_Base_Color.png", "ExitButton");
	m_exitButton.Scale(glm::vec3(0.01f));

	m_handle.Create("Lighting");
	m_handle.LoadModel("./Models/Handle.obj");
	m_handle.LoadTexture("./Textures/Models/M_Door_handle_Base_Color.png", "handle");
	m_handle.Scale(glm::vec3(0.01f));

	m_lightSwitch.Create("Lighting");
	m_lightSwitch.LoadModel("./Models/Light_switch.obj");
	m_lightSwitch.LoadTexture("./Textures/Models/M_Light_switch_Base_Color.png", "LightSwitch");
	m_lightSwitch.Scale(glm::vec3(0.01f));

	m_magnetLock.Create("Lighting");
	m_magnetLock.LoadModel("./Models/Magnet_lock.obj");
	m_magnetLock.LoadTexture("./Textures/Models/M_Door_metal_elements_Base_Color.png", "MagnetLock");
	m_magnetLock.Scale(glm::vec3(0.01f));

	m_metalElements.Create("Lighting");
	m_metalElements.LoadModel("./Models/Metal_elements.obj");
	m_metalElements.LoadTexture("./Textures/Models/M_Door_metal_elements_Base_Color.png", "MagnetLock");
	m_metalElements.Scale(glm::vec3(0.01f));
	
	m_door.Create("Lighting");
	m_door.LoadModel("./Models/Door.obj");
	m_door.LoadTexture("./Textures/Models/M_Door_metal_elements_Base_Color.png", "Door");
	m_door.Scale(glm::vec3(0.01f));

	m_eastWall.Create("Lighting");
	m_eastWall.LoadModel("./Models/east_wall.obj");
	m_eastWall.LoadTexture("./Textures/Models/East_wall_diff.jpg", "EastWall");
	m_eastWall.Scale(glm::vec3(0.01f));

	m_westWall.Create("Lighting");
	m_westWall.LoadModel("./Models/west_wall.obj");
	m_westWall.LoadTexture("./Textures/Models/West_wall_diff.jpg", "WestWall");
	m_westWall.Scale(glm::vec3(0.01f));

	m_southWall.Create("Lighting");
	m_southWall.LoadModel("./Models/South_wall.obj");
	m_southWall.LoadTexture("./Textures/Models/South_wall_diff.jpg", "SouthWall");
	m_southWall.Scale(glm::vec3(0.01f));

	m_northWall.Create("Lighting");
	m_northWall.LoadModel("./Models/north_wall.obj");
	m_northWall.LoadTexture("./Textures/Models/north_wall_diff.jpg", "NorthWall");
	m_northWall.Scale(glm::vec3(0.01f));

	m_floor.Create("Lighting");
	m_floor.LoadModel("./Models/floor.obj");
	m_floor.LoadTexture("./Textures/Models/Floor_diif.jpg", "Floor");
	m_floor.Scale(glm::vec3(0.01f));

	m_ceiling.Create("Lighting");
	m_ceiling.LoadModel("./Models/ceiling.obj");
	m_ceiling.LoadTexture("./Textures/Models/Ceiling_diff.jpg", "Ceiling");
	m_ceiling.Scale(glm::vec3(0.01f));

	//-------------------------------------- initialize Object functions

	m_controls->OnEnter();

	m_freeCamera->SetPerspView();
	
	m_spotLight->Create();

	box->Create();


	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Create();
	};

	TheShader::Instance()->SendUniformData("Lighting_isDirectionalLight", 1);
}

//-------------------------------------------------------------------------------
//Update Function
//-------------------------------------------------------------------------------
void TestState::Update()
{
	TheInput::Instance()->Update();
	m_freeCamera->Update();
	m_freeCamera->SetPerspView();


	if (TheInput::Instance()->GetIsXClicked())
	{
		Game::Instance()->ExitGame();
	}

	//------------------------------------------------
	//UPDATE OBJECTS
	//------------------------------------------------

	m_spotLight->SetDirection(m_freeCamera->GetForward());
	m_spotLight->SetPos(m_freeCamera->GetPosition());
	
	m_spotLight->Update();


	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update();
	};
	box->Update();
	box->Translate(glm::vec3(0.01f, 0.0f, 0.0f));

	m_table.Update();
	m_pc.Update();
	m_ps4.Update();
	m_ps3.Update();
	m_pc.Update();
	m_table.Update();
	m_sofa.Update();
	m_wii.Update();
	m_amp.Update();
	m_pouffe.Update();
	m_subwoofer.Update();
	m_tv.Update();
	m_aircon.Update();
	m_emergencyButton.Update();
	m_exitButton.Update();
	m_handle.Update();
	m_lightSwitch.Update();
	m_magnetLock.Update();
	m_metalElements.Update();
	m_door.Update();
	m_eastWall.Update();
	m_westWall.Update();
	m_southWall.Update();
	m_northWall.Update();
	m_floor.Update();
	m_ceiling.Update();

	//------------------------------------------------
	//DRAW OBJECTS
	//------------------------------------------------

	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Draw();
	};

	//Draw camera
	m_freeCamera->Draw();


	//Draw SpotLight
	m_spotLight->Draw();


	box->Draw();
	m_table.Draw();
	m_pc.Draw();
	m_ps4.Draw();
	m_ps3.Draw();
	m_table.Draw();
	m_sofa.Draw();
	m_wii.Draw();
	m_amp.Draw();
	m_pouffe.Draw();
	m_subwoofer.Draw();
	m_tv.Draw();
	m_aircon.Draw();
	m_emergencyButton.Draw();
	m_exitButton.Draw();
	m_handle.Draw();
	m_lightSwitch.Draw();
	m_magnetLock.Draw();
	m_metalElements.Draw();
	m_door.Draw();
	m_eastWall.Draw();
	m_westWall.Draw();
	m_southWall.Draw();
	m_northWall.Draw();
	m_floor.Draw();
	m_ceiling.Draw();

	//------------------------------------------------
	//CHECK IF TOON SHADER IS BEING USED
	//------------------------------------------------
	if (m_isToonOn)
	{
		m_table.SetShader("Toon");
		m_pc.SetShader("Toon");
		m_pouffe.SetShader("Toon");
		m_ps3.SetShader("Toon");
		m_ps4.SetShader("Toon");
		m_wii.SetShader("Toon");
		m_tv.SetShader("Toon");
		m_subwoofer.SetShader("Toon");
		m_sofa.SetShader("Toon");
		m_speaker.SetShader("Toon");
		m_amp.SetShader("Toon");
		m_aircon.SetShader("Toon");
		m_emergencyButton.SetShader("Toon");
		m_exitButton.SetShader("Toon");
		m_handle.SetShader("Toon");
		m_lightSwitch.SetShader("Toon");
		m_magnetLock.SetShader("Toon");
		m_metalElements.SetShader("Toon");
		m_door.SetShader("Toon");
		m_walls.SetShader("Toon");
	}
	else
	//------------------------------------------------
	//CHECK IF IT IS USING THE LIGHTING SHADER
	//------------------------------------------------
	{
		m_table.SetShader("Lighting");
		m_pc.SetShader("Lighting");
		m_pouffe.SetShader("Lighting");
		m_ps3.SetShader("Lighting");
		m_ps4.SetShader("Lighting");
		m_wii.SetShader("Lighting");
		m_tv.SetShader("Lighting");
		m_subwoofer.SetShader("Lighting");
		m_sofa.SetShader("Lighting");
		m_speaker.SetShader("Lighting");
		m_amp.SetShader("Lighting");
		m_aircon.SetShader("Lighting");
		m_emergencyButton.SetShader("Lighting");
		m_exitButton.SetShader("Lighting");
		m_handle.SetShader("Lighting");
		m_lightSwitch.SetShader("Lighting");
		m_magnetLock.SetShader("Lighting");
		m_metalElements.SetShader("Lighting");
		m_door.SetShader("Lighting");
		m_walls.SetShader("Lighting");
	}

	KeyState keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_T])
	{
		m_isToonOn = true;
	}
	else if (keys[SDL_SCANCODE_Y])
	{
		m_isToonOn = false;
	}

	m_uiCamera->Draw();
	m_uiCamera->SetOrthoView();
	m_controls->Draw();
}

//-------------------------------------------------------------------------------
//OnExit
//-------------------------------------------------------------------------------
void TestState::OnExit()
{
	delete(this);
}
