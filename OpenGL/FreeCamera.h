#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "Camera.h"

class FreeCamera : public Camera
{

public:

	FreeCamera();
	~FreeCamera();

public:

	void Create() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

public:

	void CheckKeyInput() override;
	void CheckControllerLeftJoystick() override;
	void CheckControllerRightJoystick() override;

public:

	glm::vec3 GetForward();
	glm::vec3 GetPosition();

private:

	glm::ivec2 mouseMotion;
	int m_screenWidth;
	int m_screenHeight;

};


#endif

