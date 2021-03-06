#include "Prop.h"

//-------------------------------------------------------------------------------
//Translate
//-------------------------------------------------------------------------------
void Prop::Translate(glm::vec3 v3)
{
	primitive->Translate(v3);
}

//-------------------------------------------------------------------------------
//Rotate
//-------------------------------------------------------------------------------
void Prop::Rotate(float angle, glm::vec3 v3)
{
	primitive->Rotate(angle, v3);
}

//-------------------------------------------------------------------------------
//Scale	
//-------------------------------------------------------------------------------
void Prop::Scale(glm::vec3 v3)
{
	primitive->Scale(v3);
}

//-------------------------------------------------------------------------------
//Set IsLit
//-------------------------------------------------------------------------------
void Prop::SetIsLit(bool b)
{
	primitive->SetIsLit(b);
}
