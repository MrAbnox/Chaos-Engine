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
	//----------------------------- Initialize Managers

	isRunning = true;
	//Enable depth test
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);

	//-------------------------------------- Create objects in the scene

	//m_spotLight = new Light(SPOTLIGHT);

	//CreateObject(new Light(POINTLIGHT));
	//CreateObject(new SkyBox);
	//m_directionalLight = new Light(DIRECTIONALLIGHT);
	CreateObject(new Floor(WOOD, glm::vec3(0.0f, 0.0f, 1.0f))); 
	//CreateObject(new Wall(BRICKS, LEFT, glm::vec3(0.0f, 0.0f, 0.0f))); 
	//CreateObject(new Box(CRATE, glm::vec3(0.0f, 1.0f, 0.0f))); 

	//m_controls = new Controls();

	m_freeCamera = new FreeCamera();
	m_uiCamera = new UICamera();

	//-------------------------------------- initialize Object functions

//	m_controls->OnEnter();

	
	//m_spotLight->Create();

	for (auto& str : m_hierarchy)
	{
		str->Create();
	}

	//m_directionalLight->Create();

	TheShader::Instance()->SendUniformData("Lighting_isDirectionalLight", 1);

	lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
	//lightPos = glm::vec3(0.0f, 4.0f, 0.0f);

	//----------------------------------------SHADOWS

	TheScreen::Instance()->GetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	glGenFramebuffers(1, &depthMapFBO);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//----------------------------------------

	near_plane = 1.0f;
	far_plane = 7.5f;


	TheShader::Instance()->SendUniformData("ShadowMapping_diffuseTexture", 0);
	TheShader::Instance()->SendUniformData("ShadowMapping_shadowMap", 1);


}

//-------------------------------------------------------------------------------
//Update Function
//-------------------------------------------------------------------------------
void TestState::Update()
{
	TheInput::Instance()->Update();
	m_freeCamera->SetPerspView();

	if (TheInput::Instance()->GetIsXClicked())
	{
		Game::Instance()->ExitGame();
	}
	//------------------------------------------------
	//UPDATE OBJECTS
	//------------------------------------------------
	//Reset Viewport
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 1. first render to depth map
	// ---------------------------------------------------------------------
	glm::ivec2 resolution;
	TheScreen::Instance()->GetScreenSize(resolution.x, resolution.y);

	m_lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
	m_lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//m_lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), 
    //                              glm::vec3( 0.0f, 0.0f,  0.0f), 
    //                              glm::vec3( 0.0f, 1.0f,  0.0f));  
	m_lightSpaceMatrix = m_lightProjection * m_lightView;

	TheShader::Instance()->SendUniformData("ShadowMapGen_lightSpaceMatrix", 1, GL_FALSE, m_lightSpaceMatrix);
	//glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_lightSpaceMatrix));

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	//glCullFace(GL_BACK);
	//Render scene from light's perspective 
	for (auto& str : m_hierarchy)
	{
		//Save old shader
		std::string temp = str->GetShader();
		//Use shadow Shader
		str->SetShader("ShadowMapGen");
		str->Update();
		str->Draw();
		//Reset to old shader
		str->SetShader(temp);
	}
	//glCullFace(GL_FRONT);
	//glCullFace(GL_BACK);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Reset Viewport

	//2. then render scene as normal with shadow mapping (using depth map)
	//---------------------------------------------------------------------

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//m_directionalLight->Update();
	//m_directionalLight->Draw();
	m_freeCamera->SetPerspView();
	m_freeCamera->Update();
	m_freeCamera->Draw();
	TheShader::Instance()->SendUniformData("ShadowMapping_lightPos", lightPos);
	TheShader::Instance()->SendUniformData("ShadowMapping_lightSpaceMatrix", 1, GL_FALSE, m_lightSpaceMatrix);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	//Render Scene
	for (auto& str : m_hierarchy)
	{
		//str->SetDepthMap(depthMap);
		str->Update();
		str->Draw();
		//str->UpdateTriangles();

	}

	//------------------------------------------------
	//DRAW OBJECTS
	//------------------------------------------------

	//Draw camera

	//Draw SpotLight
	//m_spotLight->Draw();

	KeyState keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_T])
	{
		lightPos.x += 0.01;
		//m_isToonOn = true;
	}
	else if (keys[SDL_SCANCODE_Y])
	{
		//m_isToonOn = false;
		lightPos.x -= 0.01;
	}

	m_uiCamera->Draw();
	m_uiCamera->SetOrthoView();
	//m_controls->Draw();
}

//-------------------------------------------------------------------------------
//OnExit
//-------------------------------------------------------------------------------
void TestState::OnExit()
{
	delete(this);
}
