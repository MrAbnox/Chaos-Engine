#include "ParallaxDemoState.h"
#include "TheDebug.h"
#include "Game.h"
#include "Box.h"
#include "Wall.h"
#include "Floor.h"
#include "TheShader.h"
#include "Cube.h"

ParallaxDemoState::~ParallaxDemoState()
{
}

//-------------------------------------------------------------------------------
//Create
//-------------------------------------------------------------------------------
void ParallaxDemoState::Create()
{
	//Initialize Managers
	isRunning = true;
	isCreated = true;

	//Enable Depth Test
	glEnable(GL_DEPTH_TEST);

	//Create objects in the scene
	freeCamera = new FreeCamera();
	uiCamera = new UICamera();

	CreateObject(new Box(C_SKYBOX, glm::vec3(0.0f)));
	CreateObject(new Wall(BRICKS, RIGHT, glm::vec3(0.0f, 0.0f, -1.0f)));

	for (auto& str : hierarchy)
	{
		str->Create();
	}

	//SHADOWS
	TheScreen::Instance()->GetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Create depth texture
	glGenFramebuffers(1, &depthMapFBO);

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

	lightPos = glm::vec3(0.5f, 1.0f, 0.3f);
	near_plane = 1.0f;
	far_plane = 7.5f;

	TheShader::Instance()->SendUniformData("ShadowMapping_diffuseTexture", 0);
	TheShader::Instance()->SendUniformData("ShadowMapping_shadowMap", 1);
	TheShader::Instance()->SendUniformData("NormalMapping_diffuseMap", 0);
	TheShader::Instance()->SendUniformData("NormalMapping_normalMap", 1);
	TheShader::Instance()->SendUniformData("NormalMapping_heightMap", 2);
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void ParallaxDemoState::Update()
{
	TheInput::Instance()->Update();
	freeCamera->SetPerspView();

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

	//first render to depth map
	//Light Projection and view Matrix 
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, 7.5f);
	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Calculate light matrix and send it.
	lightSpaceMatrix = lightProjection * lightView;
	TheShader::Instance()->SendUniformData("ShadowMapGen_lightSpaceMatrix", 1, GL_FALSE, lightSpaceMatrix);
	TheShader::Instance()->SendUniformData("NormalMapping_heightScale", heightScale);

	//Render to Framebuffer depth Map
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	//Render scene from light's perspective 
	for (auto& str : hierarchy)
	{
		//Save old shader
		std::string temp = str->GetShader();

		//Use shadow Shader
		str->SetShader("ShadowMapGen");
		if (temp != "NormalMapping")
		{
			str->Update();
			str->Draw();
		}

		//Reset to old shader
		str->SetShader(temp);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Secondly render scene as normal with shadow mapping (using depth map)
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Update Camera and Send the view and projection matrices to the ShadowMapping shader
	freeCamera->Update();
	freeCamera->Draw();

	//Send Light Pos 
	TheShader::Instance()->SendUniformData("ShadowMapping_lightPos", lightPos);
	TheShader::Instance()->SendUniformData("NormalMapping_lightPos", lightPos);

	//Send LightSpaceMatrix
	TheShader::Instance()->SendUniformData("ShadowMapping_lightSpaceMatrix", 1, GL_FALSE, lightSpaceMatrix);

	//Activate Shadow Mapping texture
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	for (auto& str : hierarchy)
	{
		str->Update();
		str->Draw();
	}

	uiCamera->Draw();
	uiCamera->SetOrthoView();
}

//-------------------------------------------------------------------------------
//OnExit
//-------------------------------------------------------------------------------
void ParallaxDemoState::OnExit()
{
}
