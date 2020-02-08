#include "Prop.h"

//-------------------------------------------------------------------------------
//Translate
//-------------------------------------------------------------------------------
void Prop::Translate(glm::vec3 v3)
{
	m_primitive->Translate(v3);
}

void Prop::Translate(glm::vec2 v2, float z)
{
	m_primitive->Translate(glm::vec3(v2, z));
}

void Prop::Translate(float x, float y, float z)
{
	m_primitive->Translate(x, y, z);
}

//-------------------------------------------------------------------------------
//Rotate
//-------------------------------------------------------------------------------
void Prop::Rotate(float angle, glm::vec3 v3)
{
	m_primitive->Rotate(angle, v3);
}

void Prop::Rotate(float angle, glm::vec2 v2, float z)
{
	m_primitive->Rotate(angle, v2, z);
}

void Prop::Rotate(float angle, float x, float y, float z)
{
	m_primitive->Rotate(angle, x, y, z);
}

//-------------------------------------------------------------------------------
//Scale	
//-------------------------------------------------------------------------------
void Prop::Scale(glm::vec3 v3)
{
	m_primitive->Scale(v3);
}

void Prop::Scale(glm::vec2 v2, float z)
{
	m_primitive->Scale(v2, z);
}

void Prop::Scale(float x, float y, float z)
{
	m_primitive->Scale(x, y, z);
}

//-------------------------------------------------------------------------------
//Set IsLit
//-------------------------------------------------------------------------------
void Prop::SetIsLit(bool b)
{
	m_primitive->SetIsLit(b);
}
