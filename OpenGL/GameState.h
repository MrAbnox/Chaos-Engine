#ifndef GAMESTATE_H
#define GAMESTATE_H

//#include "Transform.h"
#include "GameObject.h"
#include <list>

enum Primitives
{
	CUBE,
	QUAD
};

class GameState
{

public:

	GameState();
	~GameState() {}

public:

	virtual void Create() {}
	virtual void Update() {} 
	virtual void OnExit() {}

public:

	void UpdateHierarchy();

	void CreateEmpty();
	void Create(GameObject& object);
	void CreatePrimitive(Primitives& primitive);

	void DeleteObject(GameObject& object);

protected:

	bool isRunning;

public:

	bool GetIsRunning();
	void SetIsRunning(bool& isrunning);

private:

	Transform* m_worldTransform;

private:

	std::list<GameObject> Hierarchy;
};

#endif