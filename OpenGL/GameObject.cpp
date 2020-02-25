#include "GameObject.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
GameObject::GameObject()
{
	m_transform = new Transform(this);
}

//-------------------------------------------------------------------------------
//Update Function
//-------------------------------------------------------------------------------
void GameObject::Update()
{

}

//-------------------------------------------------------------------------------
//Draw Function
//-------------------------------------------------------------------------------
void GameObject::Draw()
{
	if (canSendCoords)
	{
		SendModelInformation(m_shader);
	}
}

//-------------------------------------------------------------------------------
//Send Model Information
//-------------------------------------------------------------------------------
void GameObject::SendModelInformation(const std::string shader)
{
	//Make temporary string
	std::string tempString = shader + "_model";

	//Send Model Information
	TheShader::Instance()->SendUniformData(tempString.c_str(), 1, GL_FALSE, m_transform->GetLocalToWorldCoords());
}
//-------------------------------------------------------------------------------
//Set Identity / Reset matrix
//-------------------------------------------------------------------------------
void GameObject::SetIdentity()
{
	m_transform->SetIdentity();
}

//-------------------------------------------------------------------------------
//UpdateChildren Function
//-------------------------------------------------------------------------------
void GameObject::UpdateChildren()
{
	//Check if there is at least one child
	if (GetChildrenCount() > 0)
	{
		GetTransform().UpdateCoordinates();
	}
}

//-------------------------------------------------------------------------------
//Translate
//-------------------------------------------------------------------------------
void GameObject::Translate(glm::vec3 v3)
{
	m_transform->Translate(v3);
}

//-------------------------------------------------------------------------------
//Rotate
//-------------------------------------------------------------------------------
void GameObject::Rotate(float angle, glm::vec3 v3)
{
	m_transform->Rotate(angle, v3);
}

//-------------------------------------------------------------------------------
//Scale	
//-------------------------------------------------------------------------------
void GameObject::Scale(glm::vec3 v3)
{
	m_transform->Scale(v3);
}

//-------------------------------------------------------------------------------
//Set Active
//-------------------------------------------------------------------------------
void GameObject::SetIsEnabled(const bool& value)
{
	m_isEnabled = value;
}

//-------------------------------------------------------------------------------
//Get Active
//-------------------------------------------------------------------------------
bool GameObject::GetIsEnabled() const
{
	return m_isEnabled;
}

//-------------------------------------------------------------------------------
//Get Children Count
//-------------------------------------------------------------------------------
int GameObject::GetChildrenCount() const
{
	return m_transform->GetChildrenCount();
}

//-------------------------------------------------------------------------------
//Get Transform
//-------------------------------------------------------------------------------
Transform GameObject::GetTransform() const
{
	return *m_transform;
}

//-------------------------------------------------------------------------------
//Add Component
//-------------------------------------------------------------------------------
void GameObject::AddComponent(Component& component)
{
	//Check if component is transform
	if (component.GetName() == "Transform")
	{
		TheDebug::Log("Can't Add Transform Component to object since object already has component.", ALERT);
	}
	else
	{
		//Add Component
		m_components.push_back(component);
	}
}

//-------------------------------------------------------------------------------
//Remove Component
//-------------------------------------------------------------------------------
void GameObject::RemoveComponent(Component& component)
{
	//Check it if is the transform component
	if (component.GetName() == "Transform")
	{
		TheDebug::Log("Can't remove Transform Component from object since object always need a Transform", ALERT);
	}
	else
	{
		//Remove Component
		for (std::list<Component>::iterator it = m_components.begin(), end = m_components.end(); it != end; ++it)
		{	
			//it->Destroy();
			delete(&it);
		}
	}
}

//-------------------------------------------------------------------------------
//Set Component Active
//-------------------------------------------------------------------------------
void GameObject::SetComponentActive(Component& component, bool& value)
{
	//Set specific Component to active or not
	//Check if Component is a transform
	if (component.GetName() == "Transform")
	{
		TheDebug::Log("Can't set Transform Component's to active or deactivated.", ALERT);
	}
	else
	{
		for (std::list<Component>::iterator it = m_components.begin(), end = m_components.end(); it != end; ++it)
		{
			it->SetActive(value);
		}
	}
}

//-------------------------------------------------------------------------------
//Set Shader
//-------------------------------------------------------------------------------
std::string GameObject::GetShader() const
{
	return m_shader;
}

//-------------------------------------------------------------------------------
//Set Shader
//-------------------------------------------------------------------------------
void GameObject::SetShader(std::string shader)
{
	m_shader = shader;
}

//-------------------------------------------------------------------------------
//Set is Highlighted (This function will eventually need to be removed)
//-------------------------------------------------------------------------------
void GameObject::SetIsHighlighted(int i)
{
	m_isHighlighted = i;
}
