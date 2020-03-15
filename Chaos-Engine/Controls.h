#ifndef CONTROLS_H
#define CONTROLS_H

#include "UI.h"
#include "Quad.h"

#include <glm.hpp>

class Controls : public UI
{
public:

	Controls();
	~Controls();

public:

	void OnEnter() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;
};

#endif