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

private:

	void CheckInput();
	void SendProjData();
	void SendViewData();
	void SendPos();
	void SetView();

public:

	glm::vec3 GetForward();
	glm::vec3 GetPosition();

private:

	glm::ivec2 mouseMotion;
	int screenWidth;
	int screenHeight;
};


#endif

