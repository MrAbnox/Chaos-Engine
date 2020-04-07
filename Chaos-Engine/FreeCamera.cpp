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
	TheScreen::Instance()->GetScreenSize(m_screenWidth, m_screenHeight);

	projID = TheShader::Instance()->GetUniformID("ShadowMapping_projection");
	projID = TheShader::Instance()->GetUniformID("NormalMapping_projection");
	viewID = TheShader::Instance()->GetUniformID("ShadowMapping_view");
	viewID = TheShader::Instance()->GetUniformID("NormalMapping_view");

	m_view = glm::mat4(1.0f);
	m_proj = glm::mat4(1.0f);

	mouseMotion = glm::ivec2(0);

	m_velocity = 0.02f;
	m_sensitivity = 0.15f;
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_camPos = glm::vec3(0.0f, 1.0f, 1.0f);
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

		yaw += mouseMotion.x * m_sensitivity;
		pitch -= mouseMotion.y * m_sensitivity;

		m_forward.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
		m_forward.y = glm::sin(glm::radians(pitch));
		m_forward.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));


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
			Ray ray = Ray(m_camPos, m_proj, m_view);

			Physics physics;

			std::list<GameObject*> tempHierarchy = Game::Instance()->GetCurrentScene()->GetHierarchy();

			for (auto& str : tempHierarchy)
			{
				if (physics.RayABB(ray.GetDirection(), m_camPos, str->GetCollider()))
				{
					Game::Instance()->GetCurrentScene()->SetSelectedObject(str);
				}
			}

		}
	}
	else
	{
	}

	m_view = glm::lookAt(m_camPos, //pos 
		m_camPos + m_forward, //target
		m_up); //up

	TheShader::Instance()->SendUniformData("Lighting_cameraPos", m_camPos);
	TheShader::Instance()->SendUniformData("ShadowMapping_viewPos", m_camPos);
	TheShader::Instance()->SendUniformData("NormalMapping_viewPos", m_camPos);
	TheShader::Instance()->SendUniformData("LightMap_cameraPos", m_camPos);
	TheShader::Instance()->SendUniformData("Toon_cameraPos", m_camPos);
	TheShader::Instance()->SendUniformData("Cubemap_cameraPos", m_camPos);
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void FreeCamera::Draw()
{

	//----------------------------- Set Viewport

	glViewport(0, 0, m_screenWidth, m_screenHeight);

	//----------------------------- Send view and projection matrix to Lamp shaders
	TheShader::Instance()->SendUniformData("Lightless_view", 1, GL_FALSE, m_view);
	TheShader::Instance()->SendUniformData("Lightless_projection", 1, GL_FALSE, m_proj);

	//----------------------------- Send view and projection matrix to Light shaders
	TheShader::Instance()->SendUniformData("Lighting_view", 1, GL_FALSE, m_view);
	TheShader::Instance()->SendUniformData("Lighting_projection", 1, GL_FALSE, m_proj);

	//----------------------------- Send view and projection matrix to Light Map shaders
	TheShader::Instance()->SendUniformData("LightMap_view", 1, GL_FALSE, m_view);
	TheShader::Instance()->SendUniformData("LightMap_projection", 1, GL_FALSE, m_proj);

	//----------------------------- Send view and projection matrix to Toon shaders
	TheShader::Instance()->SendUniformData("Toon_view", 1, GL_FALSE, m_view);						
	TheShader::Instance()->SendUniformData("Toon_projection", 1, GL_FALSE, m_proj);

	//----------------------------- Send view and projection matrix to ShadowMapping shaders
	TheShader::Instance()->SendUniformData("ShadowMapping_view", 1, GL_FALSE, m_view);
	TheShader::Instance()->SendUniformData("ShadowMapping_projection", 1, GL_FALSE, m_proj);

	//----------------------------- Send view and projection matrix to NormalMapping shaders
	TheShader::Instance()->SendUniformData("NormalMapping_view", 1, GL_FALSE, m_view);
	TheShader::Instance()->SendUniformData("NormalMapping_projection", 1, GL_FALSE, m_proj);

	//----------------------------- Send view and projection matrix to Cubemap shaders
	TheShader::Instance()->SendUniformData("Cubemap_view", 1, GL_FALSE, m_view);
	TheShader::Instance()->SendUniformData("Cubemap_projection", 1, GL_FALSE, m_proj);

	//----------------------------- Send view and projection matrix to skybox shaders
	glm::mat4 view = glm::mat4(glm::mat3(m_view));
	TheShader::Instance()->SendUniformData("Skybox_view", 1, GL_FALSE, view);
	TheShader::Instance()->SendUniformData("Skybox_projection", 1, GL_FALSE, m_proj);
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
		m_camPos -= m_forward * m_velocity;
	}
	else if (keys[SDL_SCANCODE_W])
	{
		m_camPos += m_forward * m_velocity;
	}
	else if (keys[SDL_SCANCODE_A])
	{
		m_camPos -= glm::normalize(glm::cross(m_forward, m_up)) * m_velocity;
	}
	else if (keys[SDL_SCANCODE_D])
	{
		m_camPos += glm::normalize(glm::cross(m_forward, m_up)) * m_velocity;
	}
	else if (keys[SDL_SCANCODE_Q])
	{
		glm::vec3 right = glm::cross(m_forward, m_up);
		glm::vec3 up = glm::normalize(glm::cross(m_forward, right));
		m_camPos += up * m_velocity;
	}
	else if (keys[SDL_SCANCODE_E])
	{
		glm::vec3 right = glm::cross(m_forward, m_up);
		glm::vec3 up = glm::normalize(glm::cross(m_forward, right));
		m_camPos -= up * m_velocity;
	}

	if (m_camPos.x < -2.0f)
	{
		m_camPos.x = -2.0f;
	}

	if (m_camPos.x > 1.8f)
	{
		m_camPos.x = 1.8f;
	}

	if (m_camPos.z < -2.3f)
	{
		m_camPos.z = -2.3f;
	}

	if (m_camPos.z > 2.4f)
	{
		m_camPos.z = 2.4f;
	}

	if (m_camPos.y < 0.15f)
	{
		m_camPos.y = 0.15f;
	}

	if (m_camPos.y > 2.15f)
	{
		m_camPos.y = 2.15f;
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
			m_camPos += glm::normalize(glm::cross(m_forward, m_up)) * m_velocity;
		}

		if (TheInput::Instance()->GetJoystickXValue(0, 1) < 0)
		{
			m_camPos -= glm::normalize(glm::cross(m_forward, m_up)) * m_velocity;
		}

		if (TheInput::Instance()->GetJoystickYValue(0, 1) > 0 )
		{
			m_camPos -= m_forward * m_velocity;
		}
		if(TheInput::Instance()->GetJoystickYValue(0, 1) < 0)
		{
			m_camPos += m_forward * m_velocity;
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
	return m_forward;
}

//-------------------------------------------------------------------------------
//Get Camera Position
//-------------------------------------------------------------------------------
glm::vec3 FreeCamera::GetPosition()
{
	return m_camPos;
}
