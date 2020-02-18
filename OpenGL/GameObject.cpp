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
//Send Model Information
//-------------------------------------------------------------------------------
void GameObject::SendModelInformation(const std::string shader)
{
	//Make temporary string
	std::string tempString = shader + "_model";

	//Send Model Information
	TheShader::Instance()->SendUniformData(tempString.c_str(), 1, GL_FALSE, m_transform->GetModel());
}
//-------------------------------------------------------------------------------
//Set Identity / Reset matrix
//-------------------------------------------------------------------------------
void GameObject::SetIdentity()
{
	m_transform->SetIdentity();
}

//-------------------------------------------------------------------------------
//Translate
//-------------------------------------------------------------------------------
void GameObject::Translate(glm::vec3 v3)
{
	m_transform->Translate(v3);
}

void GameObject::Translate(glm::vec2 v2, float z)
{
	m_transform->Translate(v2, z);
}

void GameObject::Translate(float x, float y, float z)
{
	m_transform->Translate(x, y, z);
}

//-------------------------------------------------------------------------------
//Rotate
//-------------------------------------------------------------------------------
void GameObject::Rotate(float angle, glm::vec3 v3)
{
	m_transform->Rotate(angle, v3);
}

void GameObject::Rotate(float angle, glm::vec2 v2, float z)
{
	m_transform->Rotate(angle, v2, z);
}

void GameObject::Rotate(float angle, float x, float y, float z)
{
	m_transform->Rotate(angle, x, y, z);
}
//-------------------------------------------------------------------------------
//Scale	
//-------------------------------------------------------------------------------
void GameObject::Scale(glm::vec3 v3)
{
	m_transform->Scale(v3);
}

void GameObject::Scale(glm::vec2 v2, float z)
{
	m_transform->Scale(v2, z);
}

void GameObject::Scale(float x, float y, float z)
{
	m_transform->Scale(x, y, z);
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
}

//-------------------------------------------------------------------------------
//Remove Component
//-------------------------------------------------------------------------------
void GameObject::RemoveComponent(Component& component)
{
	//Remove specific component
	//Check it if is the transform component
}

//-------------------------------------------------------------------------------
//Set Component Active
//-------------------------------------------------------------------------------
void GameObject::SetComponentActive(Component& component, const bool& value)
{
	//Set specific Component to active or not
	//Check if Component is a transform
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
