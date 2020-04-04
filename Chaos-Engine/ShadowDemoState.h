#ifndef SHADOWDEMOSTATE_H
#define SHADOWDEMOSTATE_H
#include "Grid.h"
#include "Light.h"
#include "Model.h"
#include "SkyBox.h"
#include "UICamera.h"
#include "Controls.h"
#include "GameState.h"
#include "Transform.h"
#include "GameState.h"
#include "TheScreen.h"
#include "FreeCamera.h"

class ShadowDemoState : public GameState
{

public:

	ShadowDemoState();
	~ShadowDemoState();

public:

	void Create() override;
	void Update() override;
	void OnExit() override;

private:

	FreeCamera* m_freeCamera;
	UICamera* m_uiCamera;
	Grid* m_grid;
	Controls* m_controls;
	Light* m_directionalLight;

private:

	Texture* m_shadowMapTexture;

private:

	bool m_isToonOn;

private:

	glm::mat4 m_lightProjection;
	glm::mat4 m_lightView;
	glm::mat4 m_lightSpaceMatrix;

	Model m_floor;
	Model m_moon;

private:

	glm::vec3 lightPos;

private:

	float near_plane, far_plane;
	float heightScale = 0.1f;

private:


	unsigned int depthMapFBO;
	unsigned int depthMap;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
};

#endif