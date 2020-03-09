#include "AABB.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
AABB::AABB()
{
	m_dimension = glm::vec3(1.0f);
	m_position = glm::vec3(0.0f);
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
AABB::~AABB()
{
}

//-------------------------------------------------------------------------------
//Set position
//-------------------------------------------------------------------------------
void AABB::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Dimension
//-------------------------------------------------------------------------------
void AABB::SetDimension(float width, float height, float depth)
{
	m_dimension = glm::vec3(width, height, depth);
}

//-------------------------------------------------------------------------------
//Box to Box colliding
//-------------------------------------------------------------------------------
bool AABB::IsColliding(const AABB& secondBox)
{
	if (m_max.x > secondBox.m_min.x&& secondBox.m_max.x > m_min.x&&
		m_max.y > secondBox.m_min.y&& secondBox.m_max.y > m_min.y&&
		m_max.z > secondBox.m_min.z&& secondBox.m_max.z > m_min.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------------
//Sphere to Sphere collision
//-------------------------------------------------------------------------------
bool AABB::IsColliding(SphereCollision& second)
{
	//Distance Beetween The bounds
	m_distance = m_position - second.GetPosition();

	m_distanceFromBound = sqrt(m_distance.x * m_distance.x +
		m_distance.y * m_distance.y +
		m_distance.z * m_distance.z);

	// Half of the Widh, Height and depth
	m_halfDimension = m_dimension * .5f;

	// Clamps m_clamped = glm::clamp(m_distance, -m_halfDimension, m_halfDimension);
	m_clamped = glm::clamp(m_distance, -m_halfDimension, m_halfDimension);

	// nearest edge point
	m_pointOnEdge = m_position - m_clamped;

	return (glm::distance(second.GetPosition(), m_pointOnEdge) <= second.GetRadius());

}

//-------------------------------------------------------------------------------
//Get Min
//-------------------------------------------------------------------------------
glm::vec3 AABB::GetMin()
{
	return m_min;
}

//-------------------------------------------------------------------------------
//Get Max
//-------------------------------------------------------------------------------
glm::vec3 AABB::GetMax()
{
	return m_max;
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void AABB::Update()
{
	glm::vec3 halfDimension = m_dimension / 2.0f;

	m_min.x = m_position.x - halfDimension.x;
	m_max.x = m_position.x + halfDimension.x;

	m_min.y = m_position.y - halfDimension.x;
	m_max.y = m_position.y + halfDimension.y;

	m_min.z = m_position.z - halfDimension.z;
	m_max.z = m_position.z + halfDimension.z;
}

void AABB::Draw()
{
//#ifdef DEBUG
//	TheDebug::Instance()->DrawCube3D(m_dimension.x,
//		m_dimension.y,
//		m_dimension.z,
//		1.0f, 0.0f, 1.0f, 0.4f);
//#endif
}
