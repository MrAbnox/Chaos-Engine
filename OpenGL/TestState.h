#pragma once
#include "GameState.h"
#include "Grid.h"
#include "FreeCamera.h"
#include "Transform.h"
#include "GameState.h"
#include "SkyBox.h"
#include "Controls.h"
#include "UICamera.h"
#include "Model.h"
#include "Light.h"

#include <vector>

class TestState : public GameState
{
public:

	void Create() override;
	void Update() override;
	void OnExit() override;

private:

	FreeCamera* m_freeCamera;
	UICamera* m_uiCamera;
	Grid* m_grid;
	Controls* m_controls;
	Light* m_spotLight;

private:

	Model m_table;
	Model m_pc;
	Model m_pouffe;
	Model m_ps3;
	Model m_ps4;
	Model m_wii;
	Model m_tv;
	Model m_subwoofer;
	Model m_sofa;
	Model m_speaker;
	Model m_amp;
	Model m_aircon;
	Model m_emergencyButton;
	Model m_exitButton;
	Model m_handle;
	Model m_lightSwitch;
	Model m_magnetLock;
	Model m_metalElements;
	Model m_door;
	Model m_walls;
	Model m_eastWall;
	Model m_westWall;
	Model m_northWall;
	Model m_southWall;
	Model m_floor;
	Model m_ceiling;
private:

	bool m_isToonOn;
	Box* box;

private:

	GLuint shadowFBO;
};

