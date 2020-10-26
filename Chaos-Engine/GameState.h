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
	~GameState() { delete selectedObject; }

public:

	virtual void Create() {}
	virtual void Update();
	virtual void OnExit() {}

public:

	void UpdateHierarchy();

	void AddObject(GameObject* object);

	void CreateEmpty();
	void CreateObject(GameObject* object);
	void AddExistingObject(GameObject* object);
	void CreatePrimitive(Primitives& primitive);

	void DeleteObject(GameObject& object);

protected:

	bool isRunning;
	bool isWorldCordSet;
	bool isCreated;

public:

	bool GetIsRunning();
	void SetIsRunning(bool& isrunning);

public:

	bool GetIsCreated() const;
	std::list<GameObject*> GetHierarchy() const;
	GameObject* GetSelectedObject() const;

public:

	void SetSelectedObject(GameObject* object);

private:

	GameObject* selectedObject;

protected:

	std::list<GameObject*> hierarchy;

private:
};

#endif