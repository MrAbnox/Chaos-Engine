#ifndef UICAMERA_H
#define UICAMERA_H
#include "Camera.h"
class UICamera : public Camera
{
public:

	UICamera();
	~UICamera();

public:

	void Create() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

private:

	int m_screenWidth;
	int m_screenHeight;
};

#endif