#include "Transform.h"
#include <gtc/matrix_transform.hpp>
#include "TheShader.h"
#include <gtc/quaternion.hpp>

const glm::mat4 Transform::s_worldCoords;

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Transform::Transform()
{
	m_name = "Transform";

	isDirty = false;
	isInverseDirty = false;
}

//-------------------------------------------------------------------------------
//Constructor GameObject overload
//-------------------------------------------------------------------------------
Transform::Transform(GameObject* object)
{
	m_name = "Transform";

	m_model = glm::mat4(1.0f);

	m_localPos = glm::vec3(0.0f);
	m_localRotation = glm::vec3(0.0f);
	m_localScale = glm::vec3(0.0f);

	isDirty = false;
	isInverseDirty = false;
}

Transform::Transform(GameState* gamestate)
{
//-------------------------------------------------------------------------------
//Constructor GameState Overload
//-------------------------------------------------------------------------------
	m_name = "Transform";

	m_model = glm::mat4(1.0f);

	m_localPos = glm::vec3(0.0f);
	m_localRotation = glm::vec3(0.0f);
	m_localScale = glm::vec3(0.0f);

	isDirty = false;
	isInverseDirty = false;
}

//-------------------------------------------------------------------------------
//Reset Transformations
//-------------------------------------------------------------------------------
void Transform::SetIdentity()
{
	//Reset Matrix
	m_model = glm::mat4(1.0f);
}

//-------------------------------------------------------------------------------
//Set Dirty
//-------------------------------------------------------------------------------
void Transform::SetDirty()
{
	//Only set dirty if it is not dirty yet
	if (!isDirty)
	{
		isDirty = true;
		isInverseDirty = true;

		//If there is at least one child, set them dirty too.
		if (m_childrenCount > 0)
		{
			for (auto& str : m_children)
			{
				str.SetDirty();
			}
		}
	}
}

//-------------------------------------------------------------------------------
//Calculate Local Matrix to Parent Matrix 
//-------------------------------------------------------------------------------
glm::mat4 Transform::calculateLocalToParentMatrix()
{
	glm::mat4 tempMatrix;

	if (!m_parent)
	{	
		//if there is no parent calculate matrix relative to world cords
		tempMatrix = m_localToParentCoords * s_worldCoords;
	}
	else
	{
		//if there is a parent calculate matrix relative to all parents
		tempMatrix = m_parent->calculateLocalToParentMatrix() * m_localToParentCoords;
	}

	return tempMatrix;
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

	//Set Parent Local Matrix to this object's parent matrix
	m_localToParentCoords = transform.GetLocalCords();
}

//-------------------------------------------------------------------------------
//Destroy Child by int
//-------------------------------------------------------------------------------
void Transform::DestroyChild(const int& child)
{
	//Check if there is at least one child
	if (m_childrenCount > 0)
	{
		//Remove from child count
		m_childrenCount--;

		//Temp variable
		int i = 0;

		//Loop through List and find child number
		for (auto& str : m_children)
		{
			if (i == child)
			{
				m_children.remove(str);
			}
		}
	}
}

//-------------------------------------------------------------------------------
//Destroy Child by Transform
//-------------------------------------------------------------------------------
void Transform::DestroyChild(Transform& child)
{
	//Check if there is at least one child
	if (m_childrenCount > 0)
	{
		//Remove from child count
		m_childrenCount--;

		//Remove child
		m_children.remove(child);
	}
}

//-------------------------------------------------------------------------------
//Destroy Child By Name
//-------------------------------------------------------------------------------
void Transform::DestroyChildByName(const std::string& child)
{
	if (child != "Transform")
	{	
		if (m_childrenCount > 0)
		{
			//Remove from child count
			m_childrenCount--;

			//Loop through List and find child name
			for (auto& str : m_children)
			{
				if (str.GetName() == child)
				{
					m_children.remove(str);
				}
			}
		}
		else
		{
			TheDebug::Log("Can't delete Children Transforms if there isn't any", ALERT);
		}
	}
	else
	{
		TheDebug::Log("Can't delete Transform Component from Object", ALERT);
	}
}

//-------------------------------------------------------------------------------
//Destroy Children
//-------------------------------------------------------------------------------
void Transform::DestroyChildren()
{
	//Check if there is at least one child
	if (GetChildrenCount() > 0)
	{
		//Loop through list and Destroy all children
		for (std::list<Transform>::iterator it = m_children.begin(), end = m_children.end(); it != end; ++it)
		{
			//If children have children, destroy them first.
			if (it->GetChildrenCount() > 0)
			{
				it->DestroyChildren();
			}

			delete(&it);
		}
	}
}

//-------------------------------------------------------------------------------
//Update Children
//-------------------------------------------------------------------------------
glm::mat4 Transform::UpdateCoordinates()
{
	glm::mat4 tempMatrix;

	if (!m_parent)
	{
		tempMatrix = m_model;
	}
	else
	{

		tempMatrix = m_parent->UpdateCoordinates() * m_model;
	}

	return tempMatrix;
}


//-------------------------------------------------------------------------------
//Update Children
//-------------------------------------------------------------------------------
void Transform::UpdateChildren()
{
	//Check if there is at least one child
	if (GetChildrenCount() > 0)
	{
		//Loop through list and Update
		for (std::list<Transform>::iterator it = m_children.begin(), end = m_children.end(); it != end; ++it)
		{
			it->UpdateCoordinates();
		}
	}
}

//-------------------------------------------------------------------------------
//Translate
//-------------------------------------------------------------------------------
void Transform::Translate(glm::vec3& v3)
{
	m_model = glm::translate(m_model, v3);

	m_localPos += v3;
}

//-------------------------------------------------------------------------------
//Rotate
//-------------------------------------------------------------------------------
void Transform::Rotate(float& angle, glm::vec3& axis)
{
	/*glm::quat quaternion = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 t = quaternion * glm::vec3(1.0f);
	m_model = glm::mat4_cast(quaternion) * m_model;*/

	m_model = glm::rotate(m_model, glm::radians(angle), axis);

	//Check which axis and add to rotation vector
	if (axis == glm::vec3(1.0f, 0.0f, 0.0f))
	{
		m_localRotation.x += angle;
	}
	else if (axis == glm::vec3(0.0f, 1.0f, 0.0f))
	{
		m_localRotation.y += angle;
	}
	else if (axis == glm::vec3(0.0f, 0.0f, 1.0f))
	{
		m_localRotation.z += angle;
	}
}

//-------------------------------------------------------------------------------
//Scale	
//-------------------------------------------------------------------------------
void Transform::Scale(glm::vec3& v3)
{
	m_model = glm::scale(m_model, v3);
}


//-------------------------------------------------------------------------------
//Set Local Pos
//-------------------------------------------------------------------------------
void Transform::SetLocalPos(const glm::vec3& pos)
{
	m_localPos = pos;
}

//-------------------------------------------------------------------------------
//Set Parent Pos
//-------------------------------------------------------------------------------
void Transform::SetParent(const Transform& parent)
{
	//Check if there is a parent
	if (m_parent != NULL)
	{
		//if yes destroy the child from parent list
		m_parent->DestroyChild(*this);
	}

	*m_parent = parent;
	
	//if there is a parent add the child
	if (m_parent)
	{
		m_parent->AddChild(*this);

		SetDirty();
	}
	else
	{
		TheDebug::Log("SetParent function is passing a NULL value", ALERT);
	}
}

//-------------------------------------------------------------------------------
//Set LocalCords
//-------------------------------------------------------------------------------
void Transform::SetLocalCoords(const glm::mat4& value)
{
	m_model = value;
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
	return s_worldCoords;
}

//-------------------------------------------------------------------------------
//Get Local Cords
//-------------------------------------------------------------------------------
glm::mat4 Transform::GetLocalCords() const
{
	return m_localToParentCoords;
}

//-------------------------------------------------------------------------------
//Set Parent
//-------------------------------------------------------------------------------
Transform* Transform::GetParent() const
{
	if (m_parent != NULL)
	{
		return m_parent;
	}
	else
	{
		TheDebug::Log("Child Transform accessed has no parent", WARNING);

		return m_parent;
	}
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
//Get GameObject
//-------------------------------------------------------------------------------
GameObject* Transform::GetGameObject()
{
	return m_object;
}
