#include "Transform.h"
#include <gtc/matrix_transform.hpp>
#include "TheShader.h"
#include <gtc/quaternion.hpp>


//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Transform::Transform()
{
	m_model = glm::mat4(1.0f);

	m_localPos = glm::vec3(0.0f);
	m_worldPos = glm::vec3(0.0f);
	m_localAngle = glm::vec3(0.0f);
	m_worldAngle = glm::vec3(0.0f);
	m_localScale = glm::vec3(0.0f);
	m_worldScale = glm::vec3(0.0f);
}

//-------------------------------------------------------------------------------
//Reset Transformations
//-------------------------------------------------------------------------------
void Transform::SetIdentity()
{
	m_model = glm::mat4(1.0f);
}

//-------------------------------------------------------------------------------
//Add Child
//-------------------------------------------------------------------------------
void Transform::AddChild(Transform& transform)
{
	//Add to child count
	m_childrenCount++;

	//Add child to list
	m_children.push_back(transform);

	//Set Child parent to this
	transform.SetParent(*this);
}

//-------------------------------------------------------------------------------
//Destroy Child by int
//-------------------------------------------------------------------------------
void Transform::DestroyChild(const int& child)
{
	//Remove from child count
	m_childrenCount--;

	//Loop through List and find child number
}

//-------------------------------------------------------------------------------
//Destroy Child By Name
//-------------------------------------------------------------------------------
void Transform::DestroyChildByName(const std::string& child)
{
	//Remove from child count
	m_childrenCount--;

	//Loop through List and find child name
}

//-------------------------------------------------------------------------------
//Destroy Children
//-------------------------------------------------------------------------------
void Transform::DestroyChildren()
{
	//Loop through list and Destroy all children
	for (std::list<Transform>::const_iterator it = m_children.begin(), end = m_children.end(); it != end; ++it)
	{
		delete(&it);
	}
}

//-------------------------------------------------------------------------------
//Translate
//-------------------------------------------------------------------------------
void Transform::Translate(glm::vec3& v3)
{
	m_model = glm::translate(m_model, v3);
}

void Transform::Translate(glm::vec2& v2, float& z)
{
	m_model = glm::translate(m_model, glm::vec3(v2, z));
}

void Transform::Translate(float& x, float& y, float& z)
{
	m_model = glm::translate(m_model, glm::vec3(x, y, z));
}

//-------------------------------------------------------------------------------
//Rotate
//-------------------------------------------------------------------------------
void Transform::Rotate(float& angle, glm::vec3& v3)
{
	glm::quat quaternion = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 t = quaternion * glm::vec3(1.0f);
	m_model = glm::mat4_cast(quaternion) * m_model;

	//m_model = glm::rotate(m_model, glm::radians(angle), v3);
}

void Transform::Rotate(float& angle, glm::vec2& v2, float& z)
{
	m_model = glm::rotate(m_model, glm::radians(angle), glm::vec3(v2, z));
}

void Transform::Rotate(float& angle, float& x, float& y, float& z)
{
	m_model = glm::rotate(m_model, glm::radians(angle), glm::vec3(x, y, z));
}

//-------------------------------------------------------------------------------
//Scale	
//-------------------------------------------------------------------------------
void Transform::Scale(glm::vec3& v3)
{
	m_model = glm::scale(m_model, v3);
}

void Transform::Scale(glm::vec2& v2, float& z)
{
	m_model = glm::scale(m_model, glm::vec3(v2, z));
}

void Transform::Scale(float& x, float& y, float& z)
{
	m_model = glm::scale(m_model, glm::vec3(x, y, z));
}

//-------------------------------------------------------------------------------
//Set Local Pos
//-------------------------------------------------------------------------------
void Transform::SetLocalPos(const glm::vec3& pos)
{
	m_localPos = pos;
}

//-------------------------------------------------------------------------------
//Set World Pos
//-------------------------------------------------------------------------------
void Transform::SetWorldPos(const glm::vec3& pos)
{
	m_worldPos = pos;
}

//-------------------------------------------------------------------------------
//Set Parent Pos
//-------------------------------------------------------------------------------
void Transform::SetParent(const Transform& parent)
{
	*m_parent = parent;
}

//-------------------------------------------------------------------------------
//Set World Cords
//-------------------------------------------------------------------------------
void Transform::SetWorldCords(const glm::mat4& value)
{
	m_worldTransform = value;
}

//-------------------------------------------------------------------------------
//Set LocalCords
//-------------------------------------------------------------------------------
void Transform::SetLocalCords(const glm::mat4& value)
{
	m_localTransform = value;
}

//-------------------------------------------------------------------------------
//Set ParentCords
//-------------------------------------------------------------------------------
void Transform::SetParentCords(const glm::mat4& value)
{
	m_parentTransform = value;
}

//-------------------------------------------------------------------------------
//Get Model
//-------------------------------------------------------------------------------
glm::mat4 Transform::GetModel() const
{
	return m_model;
}

//-------------------------------------------------------------------------------
//Get World Cords
//-------------------------------------------------------------------------------
glm::mat4 Transform::GetWorldCords() const
{
	return m_worldTransform;
}

//-------------------------------------------------------------------------------
//Get Local Cords
//-------------------------------------------------------------------------------
glm::mat4 Transform::GetLocalCords() const
{
	return m_localTransform;
}

//-------------------------------------------------------------------------------
//Get Parent Cords
//-------------------------------------------------------------------------------
glm::mat4 Transform::GetParentCords() const
{
	return m_parentTransform;
}

//-------------------------------------------------------------------------------
//Set Parent
//-------------------------------------------------------------------------------
Transform* Transform::GetParent() const
{
	return m_parent;
}

//-------------------------------------------------------------------------------
//Get Child with int
//-------------------------------------------------------------------------------
Transform Transform::GetChild(const int& child)
{
	//Loop through List and find child number and get it
	return Transform();
}

//-------------------------------------------------------------------------------
//Get Child by name
//-------------------------------------------------------------------------------
Transform Transform::GetChildByName(const std::string& child)
{
	//Loop through List and find child name and get it
	return Transform();
}

//-------------------------------------------------------------------------------
//Get Child Count
//-------------------------------------------------------------------------------
int Transform::GetChildrenCount() const
{
	return m_childrenCount;
}

//-------------------------------------------------------------------------------
//Get Local Pos
//-------------------------------------------------------------------------------
glm::vec3 Transform::GetLocalPos() const
{
	return m_localPos;
}

//-------------------------------------------------------------------------------
//Get World Pos
//-------------------------------------------------------------------------------
glm::vec3 Transform::GetWorldPos() const
{
	return m_worldPos;
}

////-------------------------------------------------------------------------------
////Get GameObject
////-------------------------------------------------------------------------------
//GameObject Transform::GetGameObject() const
//{
//	return GameObject();
//}