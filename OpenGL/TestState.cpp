#include "TestState.h"
#include "TheDebug.h"
#include "Game.h"
#include "Box.h"
#include "Wall.h"
#include "Floor.h"
#include "TheShader.h"
#include "Cube.h"

#include <iostream>

//-------------------------------------------------------------------------------
//OnEnter function
//-------------------------------------------------------------------------------
void TestState::Create()
{
	//Shadow Stuff

	TheScreen::Instance()->GetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//----------------------------- Initialize Managers

	isRunning = true;

	//-------------------------------------- Create objects in the scene

	//m_spotLight = new Light(SPOTLIGHT);

	//CreateObject(new Light(POINTLIGHT));
	CreateObject(new SkyBox);
	CreateObject(new Box(CRATE, glm::vec3(1.0f))); 
	CreateObject(new Floor(WOOD, glm::vec3(1.0f))); 
	m_directionalLight = new Light(DIRECTIONALLIGHT);

	m_controls = new Controls();

	m_freeCamera = new FreeCamera();
	m_uiCamera = new UICamera();

	//-------------------------------------- initialize Object functions

	m_controls->OnEnter();

	m_freeCamera->SetPerspView();
	
	//m_spotLight->Create();


	for (auto& str : m_hierarchy)
	{
		str->Create();
	}
	m_directionalLight->Create();

	TheShader::Instance()->SendUniformData("Lighting_isDirectionalLight", 1);


	//----------------------------------------SHADOWS

	//glGenFramebuffers(1, &depthMapFBO);

	//glGenTextures(1, &depthMap);
	//glBindTexture(GL_TEXTURE_2D, depthMap);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//----------------------------------------
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

	//m_spotLight->SetDirection(m_freeCamera->GetForward());
	//m_spotLight->SetPos(m_freeCamera->GetPosition());
	//
	//m_spotLight->Update();

	//----------------------------------------SHADOWS
	//for (auto& str : m_lights)
	{
		ShadowInfo* shadowInfo;
		shadowInfo = m_directionalLight->GetShadowInfo();

		glClear(GL_DEPTH_BUFFER_BIT);

		if (shadowInfo)
		{
			FreeCamera* tempCam = m_freeCamera;
			//m_freeCamera->SetProjection(shadowInfo->GetProjection())
			m_freeCamera->SetProjection(shadowInfo->GetProjection());
			m_freeCamera->GetTransform()->SetLocalPos(m_directionalLight->GetTransform()->GetLocalPos());
			m_freeCamera->GetTransform()->SetLocalRot(m_directionalLight->GetTransform()->GetLocalRot());

			for (auto& str : m_hierarchy)
			{
				str->Update();
			}

			m_freeCamera = tempCam;
		}

		
	}

	for (auto& str : m_hierarchy)
	{
			str->Update();
	}
	m_directionalLight->Update();
	


	//------------------------------------------------
	//DRAW OBJECTS
	//------------------------------------------------
	for (auto& str : m_hierarchy)
	{
		str->Draw();
	}

	m_directionalLight->Draw();
	//Draw camera
	m_freeCamera->Draw();


	//Draw SpotLight
	//m_spotLight->Draw();

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
