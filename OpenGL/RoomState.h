#ifndef ROOMSTATE_H
#define ROOMSTATE_H

#include "Grid.h"
#include "Model.h"
#include "SkyBox.h"
#include "UICamera.h"
#include "Controls.h"
#include "Transform.h"
#include "GameState.h"
#include "SpotLight.h"
#include "FreeCamera.h"

#include <vector>

class RoomState : public GameState
{
public:

	RoomState() {}

public:

	void Create() override;
	void Update() override;
	void OnExit() override;

private:

	FreeCamera* m_freeCamera;
	UICamera* m_uiCamera;
	Grid* m_grid;
	Controls* m_controls;
	Model m_model;
	SpotLight* m_spotLight;


private:

	std::vector<GameObject*> m_gameObjects;

};

#endif
