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
}

//-------------------------------------------------------------------------------
//Reset Transformations
//-------------------------------------------------------------------------------
void Transform::SetIdentity()
{
	m_model = glm::mat4(1.0f);
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

void Transform::AddChild(const Transform& transform)
{
}

//-------------------------------------------------------------------------------
//DestroyChild
//-------------------------------------------------------------------------------
void Transform::DestroyChild(const int& child)
{

}

void Transform::DestroyChildByName(const std::string& child)
{
}

//-------------------------------------------------------------------------------
//Get Model
//-------------------------------------------------------------------------------
glm::mat4 Transform::GetModel()
{
	return m_model;
}
