#include "Transform.h"
#include <gtc/matrix_transform.hpp>
#include "TheShader.h"


//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Transform::Transform()
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
	m_model = glm::rotate(m_model, glm::radians(angle), v3);
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
//Get Model
//-------------------------------------------------------------------------------
glm::mat4 Transform::GetModel()
{
	return m_model;
}
