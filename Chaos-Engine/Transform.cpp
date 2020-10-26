#include "Transform.h"
#include <gtc/matrix_transform.hpp>
#include "TheShader.h"
#include <gtc/quaternion.hpp>

const glm::mat4 Transform::worldCoords;

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Transform::Transform()
{
	name = "Transform";

	isDirty = false;
	isInverseDirty = false;
}

//-------------------------------------------------------------------------------
//Constructor GameObject overload
//-------------------------------------------------------------------------------
Transform::Transform(GameObject* object)
{
	name = "Transform";

	localToWorldCoords = glm::mat4(1.0f);

	localPos = glm::vec3(0.0f);
	localRotation = glm::vec3(0.0f);
	localScale = glm::vec3(0.0f);

	isDirty = false;
	isInverseDirty = false;

	//Set GameObject passed as the one used
	SetGameObject(*object);
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Transform::~Transform()
{
}

//-------------------------------------------------------------------------------
//Reset Transformations
//-------------------------------------------------------------------------------
void Transform::SetIdentity()
{
	//Reset Matrix
	localToWorldCoords = glm::mat4(1.0f);
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
		if (childrenCount > 0)
		{
			for (auto& str : children)
			{
				str.SetDirty();
			}
		}
	}
}

//-------------------------------------------------------------------------------
//Calculate Local Matrix to Parent Matrix 
//-------------------------------------------------------------------------------
glm::mat4 Transform::CalculateLocalToWorldMatrix()
{
	glm::mat4 tempMatrix;

	if (!parent)
	{	
		//if there is no parent calculate matrix relative to world cords
		tempMatrix = localToParentCoords * worldCoords;
	}
	else
	{
		//if there is a parent calculate matrix relative to all parents
		tempMatrix = parent->CalculateLocalToWorldMatrix() * localToParentCoords;
	}

	return tempMatrix;
}

//-------------------------------------------------------------------------------
//Convert local Position to World Position
//-------------------------------------------------------------------------------
glm::vec3 Transform::GetWorldPos()
{
	return glm::vec3();
}

//-------------------------------------------------------------------------------
//Convert Local Rotation to World Rotation
//-------------------------------------------------------------------------------
glm::vec3 Transform::GetWorldRot()
{
	return glm::vec3();
}

//-------------------------------------------------------------------------------
//Convert Local Scale to World Scale
//-------------------------------------------------------------------------------
glm::vec3 Transform::GetWorldScale()
{
	return glm::vec3();
}

//-------------------------------------------------------------------------------
//Add Child
//-------------------------------------------------------------------------------
void Transform::AddChild(Transform& transform)
{
	//Add to child count
	childrenCount++;

	//Add child to list
	children.push_back(transform);

	//Set Child parent to this
	transform.SetParent(*this);

	//Set Parent Local Matrix to this object's parent matrix
	localToParentCoords = transform.GetLocalCords();
}

//-------------------------------------------------------------------------------
//Destroy Child by int
//-------------------------------------------------------------------------------
void Transform::DestroyChild(const int& child)
{
	//Check if there is at least one child
	if (childrenCount > 0)
	{
		//Remove from child count
		childrenCount--;

		//Temp variable
		int i = 0;

		int temp = child;
		//Loop through List and find child number
		for (std::list<Transform>::iterator it = children.begin(), end = children.end(); it != end; ++it)
		{
			if (i == temp)
			{
				children.erase(it);
			}
			  
			i++;
		}
	}
}

//-------------------------------------------------------------------------------
//TODO:: Destroy Child by Transform
//-------------------------------------------------------------------------------
void Transform::DestroyChild(Transform& child)
{
	//Check if there is at least one child
	if (childrenCount > 0)
	{
		//Remove from child count
		childrenCount--;

		//Remove child	
		//Transform temp = child;
		//for (std::list<Transform>::iterator it = m_children.begin(), end = m_children.end(); it != end; ++it)
		//{
		//	if (it == temp)
		//	{
		//		m_children.erase(it);
		//	}
		//}
	}
}

//-------------------------------------------------------------------------------
//Destroy Child By Name TODO::Check Functionality
//-------------------------------------------------------------------------------
void Transform::DestroyChildByName(const std::string& child)
{
	if (child != "Transform")
	{	
		if (childrenCount > 0)
		{
			//Remove from child count
			childrenCount--;

			//Loop through List and find child name
			for (std::list<Transform>::iterator it = children.begin(), end = children.end(); it != end; ++it)
			{
				if (it->GetName() == child)
				{
					children.erase(it);
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
//Destroy Children TODO::Check Functionality
//-------------------------------------------------------------------------------
void Transform::DestroyChildren()
{
	//Check if there is at least one child
	if (GetChildrenCount() > 0)
	{
		//Loop through list and Destroy all children
		for (std::list<Transform>::iterator it = children.begin(), end = children.end(); it != end; ++it)
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
//TODO::Update Coordinates
//-------------------------------------------------------------------------------
void Transform::UpdateCoordinates()
{
	//first check if it is dirty
	if (isDirty)
	{
		//Update localToWorld matrix
		//m_localToWorldCoords =  CalculateLocalToWorldMatrix();

		//Update all Children
		//UpdateChildren();
	}
}

//-------------------------------------------------------------------------------
//TODO::Update Children
//-------------------------------------------------------------------------------
void Transform::UpdateChildren()
{
	//Check if there is at least one child
	if (GetChildrenCount() > 0)
	{
		//Loop through list and Update
		for (std::list<Transform>::iterator it = children.begin(), end = children.end(); it != end; ++it)
		{
			it->SetLocalToWorldCoords(it->GetParent()->GetLocalToWorldCoords() * it->GetLocalToWorldCoords());
			
			it->UpdateChildren();
		}
	}
}

//-------------------------------------------------------------------------------
//Translate
//-------------------------------------------------------------------------------
void Transform::Translate(glm::vec3& v3)
{
	localToWorldCoords = glm::translate(localToWorldCoords, v3);

	//Add to Local Pos
	localPos += v3;
}

//-------------------------------------------------------------------------------
//Rotate
//-------------------------------------------------------------------------------
void Transform::Rotate(float& angle, glm::vec3& axis)
{
	//TODO::Rotate with Quaternions
	/*glm::quat quaternion = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 t = quaternion * glm::vec3(1.0f);
	m_model = glm::mat4_cast(quaternion) * m_model;*/

	localToWorldCoords = glm::rotate(localToWorldCoords, glm::radians(angle), axis);

	//Check which axis and add to rotation vector
	if (axis == glm::vec3(1.0f, 0.0f, 0.0f))
	{
		localRotation.x = angle;
	}
	else if (axis == glm::vec3(0.0f, 1.0f, 0.0f))
	{
		localRotation.y = angle;
	}
	else if (axis == glm::vec3(0.0f, 0.0f, 1.0f))
	{
		localRotation.z = angle;
	}
}

//-------------------------------------------------------------------------------
//Scale	
//-------------------------------------------------------------------------------
void Transform::Scale(glm::vec3& v3)
{
	localToWorldCoords = glm::scale(localToWorldCoords, v3);

	//Check if scaling is not just the uniform
	if (v3.x != 1.0f)
	{
		localScale.x = v3.x;
	}

	if (v3.y != 1.0f)
	{
		localScale.y = v3.y;
	}

	if (v3.z != 1.0f)
	{
		localScale.z = v3.z;
	}

}

//-------------------------------------------------------------------------------
//Set isDirty to value passed
//-------------------------------------------------------------------------------
void Transform::SetNotDirty()
{
	isDirty = false;
}

//-------------------------------------------------------------------------------
//Set Local Pos
//-------------------------------------------------------------------------------
void Transform::SetLocalPos(const glm::vec3& pos)
{
	localPos = pos;
}

//-------------------------------------------------------------------------------
//Set Local Rotation
//-------------------------------------------------------------------------------
void Transform::SetLocalRot(const glm::vec3& rot)
{
	localRotation = rot;
}

//-------------------------------------------------------------------------------
//Set Parent Pos
//-------------------------------------------------------------------------------
void Transform::SetParent(const Transform& parentRef)
{
	//Check if there is a parent
	if (parent != NULL)
	{
		//if yes destroy the child from parent list
		parent->DestroyChild(*this);
	}

	*parent = parentRef;
	
	//if there is a parent add the child
	if (parent)
	{
		parent->AddChild(*this);

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
	localToWorldCoords = value;
}

//-------------------------------------------------------------------------------
//Set Model
//-------------------------------------------------------------------------------
void Transform::SetLocalToWorldCoords(const glm::mat4& mat)
{
	localToWorldCoords = mat;
}

//-------------------------------------------------------------------------------
//Get Model
//-------------------------------------------------------------------------------
glm::mat4 Transform::GetLocalToWorldCoords()
{
	return localToWorldCoords;
}

//-------------------------------------------------------------------------------
//Get Local Cords
//-------------------------------------------------------------------------------
glm::mat4 Transform::GetLocalCords() const
{
	return localToParentCoords;
}

//-------------------------------------------------------------------------------
//Set Parent
//-------------------------------------------------------------------------------
Transform* Transform::GetParent() const
{
	if (parent != NULL)
	{
		return parent;
	}
	else
	{
		TheDebug::Log("Child Transform accessed has no parent", WARNING);

		return parent;
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
	return childrenCount;
}

//-------------------------------------------------------------------------------
//Get Local Pos
//-------------------------------------------------------------------------------
glm::vec3 Transform::GetLocalPos() const
{
	return localPos;
}


//-------------------------------------------------------------------------------
//Get Local Rotation
//-------------------------------------------------------------------------------
glm::vec3 Transform::GetLocalRot()
{
	return localRotation;
}


//-------------------------------------------------------------------------------
//Get Local Scale
//-------------------------------------------------------------------------------
glm::vec3 Transform::GetLocalScale() const
{
	return localScale;
}

//-------------------------------------------------------------------------------
//Set GameObject
//-------------------------------------------------------------------------------
void Transform::SetGameObject(GameObject& objectRef)
{
	object = &objectRef;
}

//-------------------------------------------------------------------------------
//Get GameObject
//-------------------------------------------------------------------------------
GameObject* Transform::GetGameObject()
{
	return object;
}
