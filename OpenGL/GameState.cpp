#include "GameState.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
GameState::GameState()
{
	m_worldTransform = new Transform(this);
}

//-------------------------------------------------------------------------------
//Update GameState
//-------------------------------------------------------------------------------
void GameState::Update()
{
	if (m_hierarchy.size > 0)
	{
		for (std::list<GameObject>::iterator it = m_hierarchy.begin(), end = m_hierarchy.end(); it != end; ++it)
		{
			it->GetTransform().SetWorldCoords(m_worldTransform.GetLocalToWorldCoords());
		}
	}
	//Set the gameState as the world Cords

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
void GameState::AddObject(GameObject& object)
{
	//Check if the world coordinate was already set, if not set it now
	if (isWorldCordSet == false)
	{
		isWorldCordSet = true;

		object.GetTransform().SetWorldCoords(m_worldTransform.GetLocalToWorldCoords());
	}

	//Add object to hierarchy
	m_hierarchy.push_back(object);
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
