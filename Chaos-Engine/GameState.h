#ifndef GAMESTATE_H
#define GAMESTATE_H


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
	~GameState() { delete m_selectedObject; }

public:

	virtual void Create() {}
	virtual void Update();
	virtual void OnExit() {}

public:

	void UpdateHierarchy();

	void AddObject(GameObject* object);

	void CreateEmpty();
	void CreateObject(GameObject* object);
	void CreatePrimitive(Primitives& primitive);

	void DeleteObject(GameObject& object);

protected:

	bool isRunning;

	bool isWorldCordSet;

public:

	bool GetIsRunning();
	void SetIsRunning(bool& isrunning);

public:

	std::list<GameObject*> GetHierarchy() const;
	GameObject* GetSelectedObject() const;

private:

	GameObject* m_selectedObject;

protected:

	std::list<GameObject*> m_hierarchy;

private:
};

#endif