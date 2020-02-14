#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Buffer.h"
#include "Transform.h"
#include "glad.h"

#include <glm.hpp>

class GameObject
{

protected:

	GameObject() {};
	~GameObject() {};

public:

	virtual void Create() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy() {};

public:

	void SendModelInformation(const std::string shader);
	void SetIdentity();
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

	void SetShader(std::string shader);
	void SetIsHighlighted(int i);

protected:

	bool m_isMovable;
	int m_isHighlighted;

protected:

	std::string m_shader;

protected:

	Transform m_transform;

	Buffer m_buffer;
};

#endif