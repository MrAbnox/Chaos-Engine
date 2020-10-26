#include "GameState.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
GameState::GameState()
{
}

//-------------------------------------------------------------------------------
//Update GameState
//-------------------------------------------------------------------------------
void GameState::Update()
{
}

//-------------------------------------------------------------------------------
//Update Hierarchy
//-------------------------------------------------------------------------------
void GameState::UpdateHierarchy()
{
	//Look through children
	//Update all children of children
	//Update Children
}


//-------------------------------------------------------------------------------
//Add Object to hierarchy
//-------------------------------------------------------------------------------
void GameState::AddObject(GameObject* object)
{
	//Check if the world coordinate was already set, if not set it now
	if (isWorldCordSet == false)
	{
		isWorldCordSet = true;
	}

	//Add object to hierarchy
	hierarchy.push_back(object);
}

//-------------------------------------------------------------------------------
//Create Empty GameObject
//-------------------------------------------------------------------------------
void GameState::CreateEmpty()
{
	//Create empty gameObject with just one transform
	//Set createObject's world cords to be the ones from this class
}

//-------------------------------------------------------------------------------
//Create GameObject
//-------------------------------------------------------------------------------
void GameState::CreateObject(GameObject* object)
{
	//This function will probably be used to create copy of objects
	hierarchy.push_back(object);

	//Temporary
	selectedObject = object;
}

//-------------------------------------------------------------------------------
//Add Existing GameObject
//-------------------------------------------------------------------------------
void GameState::AddExistingObject(GameObject* object)
{
	hierarchy.push_back(object);
}

//-------------------------------------------------------------------------------
//Create Primitive
//-------------------------------------------------------------------------------
void GameState::CreatePrimitive(Primitives& primitive)
{
	//Depending on what primitive is to be created,
	//Add to object list
	switch (primitive)
	{
	case CUBE:

		break;

	case QUAD:

		break;

	default:

		break;
	}
}

//-------------------------------------------------------------------------------
//Delete Object
//-------------------------------------------------------------------------------
void GameState::DeleteObject(GameObject& object)
{
	//Loop through list to delete the specified object
	//this function will probably be used 
}

//-------------------------------------------------------------------------------
//Get isRunning Function
//-------------------------------------------------------------------------------
bool GameState::GetIsRunning()
{
	return isRunning;
}


//-------------------------------------------------------------------------------
//Set isRunning Function
//-------------------------------------------------------------------------------
void GameState::SetIsRunning(bool& isrunning)
{
	isRunning = isrunning;
}

//-------------------------------------------------------------------------------
//Get is Created
//-------------------------------------------------------------------------------
bool GameState::GetIsCreated() const
{
	return isCreated;
}

//-------------------------------------------------------------------------------
//Get Hierarchy
//-------------------------------------------------------------------------------
std::list<GameObject*> GameState::GetHierarchy() const
{
	return hierarchy;
}

//-------------------------------------------------------------------------------
//Get Selected Object
//-------------------------------------------------------------------------------
GameObject* GameState::GetSelectedObject() const
{
	return selectedObject;
}

//-------------------------------------------------------------------------------
//Set Selected Object
//-------------------------------------------------------------------------------
void GameState::SetSelectedObject(GameObject* object)
{
	selectedObject = object;
}
