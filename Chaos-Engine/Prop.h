#ifndef PROP_H
#define PROP_H

#include "GameObject.h"
#include "Primitive.h"
#include "Quad.h"

class Prop : public GameObject
{
protected:

	Prop() {}
	~Prop() { delete primitive; }

public:

	virtual void Create() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy() {};

public:

	void Translate(glm::vec3 v3);

	void Rotate(float angle, glm::vec3 v3);

	void Scale(glm::vec3 v3);

public:

	void SetIsLit(bool b);

protected:

	Primitive* primitive;

};

#endif