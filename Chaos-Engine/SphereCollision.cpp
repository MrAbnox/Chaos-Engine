#include "SphereCollision.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
SphereCollision::SphereCollision()
{
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
SphereCollision::~SphereCollision()
{
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void SphereCollision::Draw()
{
}

//-------------------------------------------------------------------------------
//Sphere to Sphere collision
//-------------------------------------------------------------------------------
bool SphereCollision::IsColliding(const SphereCollision& second)
{
	// Distance Vector
	m_distanceVector = m_position - second.m_position;

	m_distance = glm::length(m_distanceVector);

	if (m_distance < m_radius + second.m_radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------------
//Set Radius
//-------------------------------------------------------------------------------
void SphereCollision::SetRadius(float radius)
{
	m_radius = radius;
}

//-------------------------------------------------------------------------------
//Set Position
//-------------------------------------------------------------------------------
void SphereCollision::SetPosition(glm::vec3 position)
{
	m_position = position;
}

//-------------------------------------------------------------------------------
//Get Radius
//-------------------------------------------------------------------------------
const float SphereCollision::GetRadius()
{
	return m_radius;
}

//-------------------------------------------------------------------------------
//Get Position
//-------------------------------------------------------------------------------
const glm::vec3 SphereCollision::GetPosition()
{
	return m_position;
}