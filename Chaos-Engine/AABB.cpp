#include "AABB.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
AABB::AABB()
{
	dimension = glm::vec3(1.0f);
	position = glm::vec3(0.0f);
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
	position = glm::vec3(x, y, z);
}

//-------------------------------------------------------------------------------
//Set Dimension
//-------------------------------------------------------------------------------
void AABB::SetDimension(float width, float height, float depth)
{
	dimension = glm::vec3(width, height, depth);
}

//-------------------------------------------------------------------------------
//Box to Box colliding
//-------------------------------------------------------------------------------
bool AABB::IsColliding(const AABB& secondBox)
{
	if (max.x > secondBox.min.x&& secondBox.max.x > min.x&&
		max.y > secondBox.min.y&& secondBox.max.y > min.y&&
		max.z > secondBox.min.z&& secondBox.max.z > min.z)
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
	distance = position - second.GetPosition();

	distanceFromBound = sqrt(distance.x * distance.x +
		distance.y * distance.y +
		distance.z * distance.z);

	// Half of the Widh, Height and depth
	halfDimension = dimension * .5f;

	// Clamps m_clamped = glm::clamp(m_distance, -m_halfDimension, m_halfDimension);
	clamped = glm::clamp(distance, -halfDimension, halfDimension);

	// nearest edge point
	pointOnEdge = position - clamped;

	return (glm::distance(second.GetPosition(), pointOnEdge) <= second.GetRadius());

}

//-------------------------------------------------------------------------------
//Get Min
//-------------------------------------------------------------------------------
glm::vec3 AABB::GetMin()
{
	return min;
}

//-------------------------------------------------------------------------------
//Get Max
//-------------------------------------------------------------------------------
glm::vec3 AABB::GetMax()
{
	return max;
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void AABB::Update()
{
	glm::vec3 halfDimension = dimension / 2.0f;

	min.x = position.x - halfDimension.x;
	max.x = position.x + halfDimension.x;

	min.y = position.y - halfDimension.x;
	max.y = position.y + halfDimension.y;

	min.z = position.z - halfDimension.z;
	max.z = position.z + halfDimension.z;
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
