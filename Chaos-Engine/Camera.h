#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera : public GameObject
{
protected:

	virtual void Create() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy() {};

protected:

	virtual void CheckKeyInput() {};
	virtual void CheckControllerLeftJoystick() {};
	virtual void CheckControllerRightJoystick() {};


public:

	enum Origin2D { TOP_LEFT, BOTTOM_LEFT };

public:

	void SetOrthoView(Origin2D origin = BOTTOM_LEFT);
	void SetPerspView(GLfloat nearClip = 0.1f, GLfloat farClip = 1000.0f);

public:

	void SetProjection(const glm::mat4& proj);

	glm::mat4 GetProjection();
	glm::mat4 GetView();

protected:

	GLfloat m_velocity;
	GLfloat m_sensitivity;


protected:

	const GLfloat FOV = 45.0f;
	const GLfloat NEAR_CLIP = 0.1f;
	const GLfloat FAR_CLIP = 1000.0f;

protected:

	glm::vec3 m_camPos = glm::vec3(0);

	glm::vec3 m_up;
	glm::vec3 m_forward;

protected:

	GLint projID;
	GLint viewID;

protected:

	glm::mat4 m_view;
	glm::mat4 m_proj;

};

#endif

