#include "GameObject.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
GameObject::GameObject()
{
	AddComponent(TRANSFORM);
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
		GetTransform()->UpdateCoordinates();
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
//Get Name
//-------------------------------------------------------------------------------
std::string GameObject::Getname() const
{
	return m_name;
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
Transform* GameObject::GetTransform() const
{
	return m_transform;
}
//-------------------------------------------------------------------------------
//Get Buffer
//-------------------------------------------------------------------------------
Buffer* GameObject::GetBuffer() const
{
	return m_buffer;
}

//-------------------------------------------------------------------------------
//Get Material
//-------------------------------------------------------------------------------
Material* GameObject::GetMaterial() const
{
	return m_material;
}

//-------------------------------------------------------------------------------
//Add Component
//-------------------------------------------------------------------------------
void GameObject::AddComponent(Components component)
{
	switch (component)
	{
	case MATERIAL:

		if (m_material == nullptr)
		{
			m_material = new Material;
		}
		else
		{
			TheDebug::Log("There is already one Material Component in object", WARNING);
		}

		break;

	case BUFFER:

		if (m_buffer == nullptr)
		{
			m_buffer = new Buffer;
		}
		else
		{
			TheDebug::Log("There is already one Buffer Component in object", WARNING);
		}

		break;

	case RENDERER:


		break;

	case TRANSFORM:

		if (m_transform == nullptr)
		{
			m_transform = new Transform(this);
		}
		else
		{
			TheDebug::Log("There is already one Transform Component in object", WARNING);
		}

		break;

	default:

		break;
	}
}


//-------------------------------------------------------------------------------
//Get Has phong
//-------------------------------------------------------------------------------
bool GameObject::GetHasPhong() const
{
	return m_hasPhong;
}

//-------------------------------------------------------------------------------
//Get Shader
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
