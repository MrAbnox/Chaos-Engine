#ifndef UI_H
#define UI_H

#include "Quad.h"
#include "GameObject.h"

class UI : public GameObject
{
protected:

	UI();
	~UI();

public:

	virtual void OnEnter() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void Destroy() {}

protected:

	Quad* m_quad;
};

#endif