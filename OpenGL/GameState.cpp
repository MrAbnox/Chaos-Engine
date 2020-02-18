#include "GameState.h"
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
//Create Empty GameObject
//-------------------------------------------------------------------------------
void GameState::CreateEmpty()
{
	//Create empty gameObject with just one transform
}

//-------------------------------------------------------------------------------
//Create GameObject
//-------------------------------------------------------------------------------
void GameState::Create(GameObject& object)
{
	//This function will probably be used to create copy of objects
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
