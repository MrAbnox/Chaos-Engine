#include "Camera.h"
#include "TheScreen.h"
#include "TheShader.h"


//-------------------------------------------------------------------------------
//Set Orthographic view	
//-------------------------------------------------------------------------------
void Camera::SetOrthoView(Origin2D origin)
{
	//----------------------------- Switch off depth testing for 2D mode
	glDisable(GL_DEPTH_TEST);

	//----------------------------- Get the screen width and height
	glm::ivec2 resolution;
	TheScreen::Instance()->GetScreenSize(resolution.x, resolution.y);

	//----------------------------- Create a 3D perspective projection using FOV angle, aspect ratio and clipping planes
	m_proj = glm::ortho(0.0f, (GLfloat)resolution.x, 0.0f, (GLfloat)resolution.y);

	//----------------------------- Send projection matrix to shader //override this functions in shader manager

	TheShader::Instance()->SendUniformData("Lighting_projection", 1, GL_FALSE, m_proj);
	TheShader::Instance()->SendUniformData("Lightless_projection", 1, GL_FALSE, m_proj);;
}

//-------------------------------------------------------------------------------
//Set Perspective view	
//-------------------------------------------------------------------------------
void Camera::SetPerspView(GLfloat nearClip, GLfloat farClip)
{
	//----------------------------- Switch on depth testing for 3d mode (later set flag so you don't clear buffer when in 3d)

	glEnable(GL_DEPTH_TEST);

	//----------------------------- Get screen height and width
	glm::ivec2 resolution;
	TheScreen::Instance()->GetScreenSize(resolution.x, resolution.y);

	//----------------------------- Calculate the aspect ratio
	const GLfloat ASPECT_RATIO = (GLfloat)resolution.x / (GLfloat)resolution.y;

	//----------------------------- Make this a setter if the person wants to
	m_proj = glm::perspective(glm::radians(FOV), ASPECT_RATIO, nearClip, farClip);

	//----------------------------- Send projection matrix to shader //overload this functions in shader manager

	TheShader::Instance()->SendUniformData("Lighting_projection", 1, GL_FALSE, m_proj);
	TheShader::Instance()->SendUniformData("Lightless_projection", 1, GL_FALSE, m_proj);

}

//-------------------------------------------------------------------------------
//Set projection
//-------------------------------------------------------------------------------
void Camera::SetProjection(const glm::mat4& proj)
{
	m_proj = proj;
}
