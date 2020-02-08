#ifndef PROP_H
#define PROP_H

#include "GameObject.h"
#include "Primitive.h"
#include "Quad.h"

class Prop : public GameObject
{
protected:

	Prop() {}
	~Prop() {}

public:

	virtual void Create() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy() {};

public:

	void Translate(glm::vec3 v3);
	void Translate(glm::vec2 v2, float z);
	void Translate(float x, float y, float z);


	void Rotate(float angle, glm::vec3 v3);
	void Rotate(float angle, glm::vec2 v2, float z);
	void Rotate(float angle, float x, float y, float z);

	void Scale(glm::vec3 v3);
	void Scale(glm::vec2 v2, float z);
	void Scale(float x, float y, float z);

public:

	void SetIsLit(bool b);

protected:

	Primitive* m_primitive;

protected:

	glm::vec3 v3_rgb;
};

#endif