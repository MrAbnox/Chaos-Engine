#include "FreeCamera.h"
#include "TheScreen.h"
#include "TheShader.h"
#include <iostream>
#include "TheInput.h"
#include "Ray.h"
#include "Physics.h"
#include "Game.h"
#include <SDL.h>


//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
FreeCamera::FreeCamera()
{
	TheScreen::Instance()->GetScreenSize(screenWidth, screenHeight);

	projID = TheShader::Instance()->GetUniformID("ShadowMapping_projection");
	projID = TheShader::Instance()->GetUniformID("NormalMapping_projection");
	viewID = TheShader::Instance()->GetUniformID("ShadowMapping_view");
	viewID = TheShader::Instance()->GetUniformID("NormalMapping_view");

	view = glm::mat4(1.0f);
	proj = glm::mat4(1.0f);

	mouseMotion = glm::ivec2(0);

	velocity = 0.02f;
	sensitivity = 0.15f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	camPos = glm::vec3(0.0f, 1.0f, 1.0f);
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
FreeCamera::~FreeCamera()
{
	Destroy();
}

//-------------------------------------------------------------------------------
//On Enter
//-------------------------------------------------------------------------------
void FreeCamera::Create()
{
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void FreeCamera::Update()
{
	//make this into one function with overloaded variables

	if (TheInput::Instance()->GetMouseButtonDown(1) || TheInput::Instance()->GetEditorMode() == false)
	{

		if (TheInput::Instance()->GetIsControllerActive())
		{
			if (TheInput::Instance()->GetJoysticksInitialized())
			{
				mouseMotion.x = TheInput::Instance()->GetMotion().x * 2;
				mouseMotion.y = TheInput::Instance()->GetMotion().y * 2;
			}
		}
		else
		{
			mouseMotion.x = TheInput::Instance()->GetMouseMotionX();
			mouseMotion.y = TheInput::Instance()->GetMouseMotionY();
		}

		static GLfloat yaw = -90.0f;
		static GLfloat pitch = 0.0f;

		yaw += mouseMotion.x * sensitivity;
		pitch -= mouseMotion.y * sensitivity;

		forward.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
		forward.y = glm::sin(glm::radians(pitch));
		forward.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));


		CheckKeyInput();
		CheckControllerLeftJoystick();
		CheckControllerRightJoystick();

		//----------------------------- Create a view matrix

	}
	else if (TheInput::Instance()->GetMouseButtonDown(0) && TheInput::Instance()->GetEditorMode())
	{
		//Create rays to select items
		//if (TheInput::Instance()->GetMouseButtonDown(0))
		{
			Ray ray = Ray(camPos, proj, view);

			Physics physics;

			std::list<GameObject*> tempHierarchy = Game::Instance()->GetCurrentScene()->GetHierarchy();

			for (auto& str : tempHierarchy)
			{
				if (physics.RayABB(ray.GetDirection(), camPos, str->GetCollider()))
				{
					Game::Instance()->GetCurrentScene()->SetSelectedObject(str);
				}
			}

		}
	}
	else
	{
	}

	view = glm::lookAt(camPos, //pos 
		camPos + forward, //target
		up); //up

	TheShader::Instance()->SendUniformData("Lighting_cameraPos", camPos);
	TheShader::Instance()->SendUniformData("ShadowMapping_viewPos", camPos);
	TheShader::Instance()->SendUniformData("NormalMapping_viewPos", camPos);
	TheShader::Instance()->SendUniformData("LightMap_cameraPos", camPos);
	TheShader::Instance()->SendUniformData("Toon_cameraPos", camPos);
	TheShader::Instance()->SendUniformData("Cubemap_cameraPos", camPos);
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void FreeCamera::Draw()
{

	//----------------------------- Set Viewport

	glViewport(0, 0, screenWidth, screenHeight);

	//----------------------------- Send view and projection matrix to Lamp shaders
	TheShader::Instance()->SendUniformData("Lightless_view", 1, GL_FALSE, view);
	TheShader::Instance()->SendUniformData("Lightless_projection", 1, GL_FALSE, proj);

	//----------------------------- Send view and projection matrix to Light shaders
	TheShader::Instance()->SendUniformData("Lighting_view", 1, GL_FALSE, view);
	TheShader::Instance()->SendUniformData("Lighting_projection", 1, GL_FALSE, proj);

	//----------------------------- Send view and projection matrix to Light Map shaders
	TheShader::Instance()->SendUniformData("LightMap_view", 1, GL_FALSE, view);
	TheShader::Instance()->SendUniformData("LightMap_projection", 1, GL_FALSE, proj);

	//----------------------------- Send view and projection matrix to Toon shaders
	TheShader::Instance()->SendUniformData("Toon_view", 1, GL_FALSE, view);						
	TheShader::Instance()->SendUniformData("Toon_projection", 1, GL_FALSE, proj);

	//----------------------------- Send view and projection matrix to ShadowMapping shaders
	TheShader::Instance()->SendUniformData("ShadowMapping_view", 1, GL_FALSE, view);
	TheShader::Instance()->SendUniformData("ShadowMapping_projection", 1, GL_FALSE, proj);

	//----------------------------- Send view and projection matrix to NormalMapping shaders
	TheShader::Instance()->SendUniformData("NormalMapping_view", 1, GL_FALSE, view);
	TheShader::Instance()->SendUniformData("NormalMapping_projection", 1, GL_FALSE, proj);

	//----------------------------- Send view and projection matrix to Cubemap shaders
	TheShader::Instance()->SendUniformData("Cubemap_view", 1, GL_FALSE, view);
	TheShader::Instance()->SendUniformData("Cubemap_projection", 1, GL_FALSE, proj);

	//----------------------------- Send view and projection matrix to skybox shaders
	glm::mat4 tempView = glm::mat4(glm::mat3(view));
	TheShader::Instance()->SendUniformData("Skybox_view", 1, GL_FALSE, tempView);
	TheShader::Instance()->SendUniformData("Skybox_projection", 1, GL_FALSE, proj);
}

//-------------------------------------------------------------------------------
//Destroy
//-------------------------------------------------------------------------------
void FreeCamera::Destroy()
{
	glDisableVertexAttribArray(projID);
	glDisableVertexAttribArray(viewID);
}

//-------------------------------------------------------------------------------
//Check for key input
//-------------------------------------------------------------------------------
void FreeCamera::CheckKeyInput()
{
	//----------------------------- Get KeyStates && update input manager


	KeyState keys = TheInput::Instance()->GetKeyStates();

	//----------------------------- Check for key presses and move camera

	if (keys[SDL_SCANCODE_S])
	{
		camPos -= forward * velocity;
	}
	else if (keys[SDL_SCANCODE_W])
	{
		camPos += forward * velocity;
	}
	else if (keys[SDL_SCANCODE_A])
	{
		camPos -= glm::normalize(glm::cross(forward, up)) * velocity;
	}
	else if (keys[SDL_SCANCODE_D])
	{
		camPos += glm::normalize(glm::cross(forward, up)) * velocity;
	}
	else if (keys[SDL_SCANCODE_Q])
	{
		glm::vec3 right = glm::cross(forward, up);
		glm::vec3 up = glm::normalize(glm::cross(forward, right));
		camPos += up * velocity;
	}
	else if (keys[SDL_SCANCODE_E])
	{
		glm::vec3 right = glm::cross(forward, up);
		glm::vec3 up = glm::normalize(glm::cross(forward, right));
		camPos -= up * velocity;
	}

	//----------------------------- Check for Keystates and set it to wireframe/polygon or point mode

	if (keys[SDL_SCANCODE_Z])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (keys[SDL_SCANCODE_X])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	else if (keys[SDL_SCANCODE_C])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

//-------------------------------------------------------------------------------
//Check Controller Left Joystick
//-------------------------------------------------------------------------------
void FreeCamera::CheckControllerLeftJoystick()
{
	//check if Joysticks are initialized
	if (TheInput::Instance()->GetJoysticksInitialized())
	{
		if (TheInput::Instance()->GetJoystickXValue(0, 1) > 0)
		{
			camPos += glm::normalize(glm::cross(forward, up)) * velocity;
		}

		if (TheInput::Instance()->GetJoystickXValue(0, 1) < 0)
		{
			camPos -= glm::normalize(glm::cross(forward, up)) * velocity;
		}

		if (TheInput::Instance()->GetJoystickYValue(0, 1) > 0 )
		{
			camPos -= forward * velocity;
		}
		if(TheInput::Instance()->GetJoystickYValue(0, 1) < 0)
		{
			camPos += forward * velocity;
		}
	}
}

//-------------------------------------------------------------------------------
//Check Controller Right Joystick
//-------------------------------------------------------------------------------
void FreeCamera::CheckControllerRightJoystick()
{
	if (TheInput::Instance()->GetJoysticksInitialized())
	{
		if (TheInput::Instance()->GetJoystickXValue(0, 2) > 0 || TheInput::Instance()->GetJoystickXValue(0, 2) < 0)
		{
			int tempint = 0;
			tempint = TheInput::Instance()->GetJoystickXValue(0, 2);
			TheInput::Instance()->SetMotionX(tempint);
		}
		else
		{
			TheInput::Instance()->SetMotionX(0);
		}

		if (TheInput::Instance()->GetJoystickYValue(0, 2) > 0 || TheInput::Instance()->GetJoystickYValue(0, 2) < 0)
		{
			int tempint = 0;
			tempint = TheInput::Instance()->GetJoystickYValue(0, 2);
			TheInput::Instance()->SetMotionY(tempint);
		}
		else
		{
			TheInput::Instance()->SetMotionY(0);
		}
	}
}

//-------------------------------------------------------------------------------
//Get Camera Forward
//-------------------------------------------------------------------------------
glm::vec3 FreeCamera::GetForward()
{
	return forward;
}

//-------------------------------------------------------------------------------
//Get Camera Position
//-------------------------------------------------------------------------------
glm::vec3 FreeCamera::GetPosition()
{
	return camPos;
}
