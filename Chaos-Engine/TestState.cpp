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

	//Enable Depth Test
	glEnable(GL_DEPTH_TEST);

	//-------------------------------------- Create objects in the scene

	m_freeCamera = new FreeCamera();
	m_uiCamera = new UICamera();



	//----------------------------------------SHADOWS
	TheScreen::Instance()->GetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	m_floor.Create("ShadowMapping");
	m_floor.LoadModel("./Models/floor.obj");
	m_floor.LoadTexture("./Textures/Models/Floor_diif.jpg", "Floor");
	//m_floor.Scale(glm::vec3(0.01f));

	m_moon.Create("ShadowMapping");
	m_moon.LoadModel("./Models/sphere.obj");
	m_moon.LoadTexture("./Textures/Moon.jpg", "Moon");
	m_moon.Translate(glm::vec3(0.0f, 1.0f, 0.0f));

	glGenFramebuffers(1, &depthMapFBO);
	//Create depth texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); // Height and Width = 1024
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	//Attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//----------------------------------------

	lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
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

	//Light Projection and view Matrix 
	m_lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, 7.5f);
	m_lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Calculate light matrix and send it.
	m_lightSpaceMatrix = m_lightProjection * m_lightView;
	TheShader::Instance()->SendUniformData("ShadowMapGen_lightSpaceMatrix", 1, GL_FALSE, m_lightSpaceMatrix);

	//Render to Framebuffer depth Map
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	//Set current Shader to ShadowMapGen
	m_floor.SetShader("ShadowMapGen");
	m_moon.SetShader("ShadowMapGen");
	//Send model Matrix to current Shader
	m_floor.Draw();
	m_moon.Draw();
	//Set current Shader back to ShadowMapping
	m_moon.SetShader("ShadowMapping");
	m_floor.SetShader("ShadowMapping");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//2. then render scene as normal with shadow mapping (using depth map)
	//---------------------------------------------------------------------

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Update Camera and Send the view and projection matrices to the ShadowMapping shader
	m_freeCamera->Update();
	m_freeCamera->Draw();

	//Send Light Pos 
	TheShader::Instance()->SendUniformData("ShadowMapping_lightPos", lightPos);
	//Send LightSpaceMatrix
	TheShader::Instance()->SendUniformData("ShadowMapping_lightSpaceMatrix", 1, GL_FALSE, m_lightSpaceMatrix);

	//Activate Shadow Mapping texture
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	
	//Send model Matrix to ShadowMapping shaders
	m_moon.Draw();	
	m_floor.Draw();

	//------------------------------------------------
	//DRAW OBJECTS
	//------------------------------------------------

	KeyState keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_T])
	{
		lightPos.z += 0.01;
		//m_isToonOn = true;
	}
	else if (keys[SDL_SCANCODE_Y])
	{
		//m_isToonOn = false;
		lightPos.z -= 0.01;
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
