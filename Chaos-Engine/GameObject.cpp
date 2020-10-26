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
//Destructor
//-------------------------------------------------------------------------------
GameObject::~GameObject()
{
	delete material;
	delete buffer;
	delete transform;
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
	TheShader::Instance()->SendUniformData(tempString.c_str(), 1, GL_FALSE, transform->GetLocalToWorldCoords());
}
//-------------------------------------------------------------------------------
//Set Identity / Reset matrix
//-------------------------------------------------------------------------------
void GameObject::SetIdentity()
{
	transform->SetIdentity();
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

void GameObject::UpdateTriangles()
{


}

//-------------------------------------------------------------------------------
//DepthMap
//-------------------------------------------------------------------------------
void GameObject::SetDepthMap(unsigned int depthmap)
{
	depthMap = depthmap;
}

//-------------------------------------------------------------------------------
//Translate
//-------------------------------------------------------------------------------
void GameObject::Translate(glm::vec3 v3)
{
	transform->Translate(v3);
}

//-------------------------------------------------------------------------------
//Rotate
//-------------------------------------------------------------------------------
void GameObject::Rotate(float angle, glm::vec3 v3)
{
	transform->Rotate(angle, v3);
}

//-------------------------------------------------------------------------------
//Scale	
//-------------------------------------------------------------------------------
void GameObject::Scale(glm::vec3 v3)
{
	transform->Scale(v3);
}

//-------------------------------------------------------------------------------
//Set Name
//-------------------------------------------------------------------------------
void GameObject::SetName(std::string nameRef)
{
	name = nameRef;
}

//-------------------------------------------------------------------------------
//Get Name
//-------------------------------------------------------------------------------
std::string GameObject::Getname() const
{
	return name;
}

//-------------------------------------------------------------------------------
//Set Active
//-------------------------------------------------------------------------------
void GameObject::SetIsEnabled(const bool& value)
{
	isEnabled = value;
}

//-------------------------------------------------------------------------------
//Get Active
//-------------------------------------------------------------------------------
bool GameObject::GetIsEnabled() const
{
	return isEnabled;
}

//-------------------------------------------------------------------------------
//Get Children Count
//-------------------------------------------------------------------------------
int GameObject::GetChildrenCount() const
{
	return transform->GetChildrenCount();
}

//-------------------------------------------------------------------------------
//Get Transform
//-------------------------------------------------------------------------------
Transform* GameObject::GetTransform() const
{
	return transform;
}
//-------------------------------------------------------------------------------
//Get Buffer
//-------------------------------------------------------------------------------
Buffer* GameObject::GetBuffer() const
{
	return buffer;
}

//-------------------------------------------------------------------------------
//Get Material
//-------------------------------------------------------------------------------
Material* GameObject::GetMaterial()
{
	return material;
}

//-------------------------------------------------------------------------------
//Add Component
//-------------------------------------------------------------------------------
void GameObject::AddComponent(Components component)
{
	switch (component)
	{
	case MATERIAL:

		if (material == nullptr)
		{
			material = new Material;
		}
		else
		{
			TheDebug::Log("There is already one Material Component in object", WARNING);
		}

		break;

	case BUFFER:

		if (buffer == nullptr)
		{
			buffer = new Buffer;
		}
		else
		{
			TheDebug::Log("There is already one Buffer Component in object", WARNING);
		}

		break;

	case RENDERER:


		break;

	case TRANSFORM:

		if (transform == nullptr)
		{
			transform = new Transform(this);
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
	return hasPhong;
}

//-------------------------------------------------------------------------------
//Get Shader
//-------------------------------------------------------------------------------
std::string GameObject::GetShader() const
{
	return shader;
}

//-------------------------------------------------------------------------------
//Set Shader 
//-------------------------------------------------------------------------------
void GameObject::SetShader(std::string shaderRef)
{
	shader = shaderRef;
}

//-------------------------------------------------------------------------------
//Set is Highlighted (This function will eventually need to be removed)
//-------------------------------------------------------------------------------
void GameObject::SetIsHighlighted(int i)
{
	isHighlighted = i;
}

//-------------------------------------------------------------------------------
//Update Collider
//-------------------------------------------------------------------------------
void GameObject::UpdateCollider()
{
	collider.SetPosition(transform->GetLocalPos().x, transform->GetLocalPos().y, transform->GetLocalPos().z);
	collider.Update();
}
