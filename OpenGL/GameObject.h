#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Buffer.h"
#include "Transform.h"
#include "Component.h"
#include "glad.h"

#include <glm.hpp>
#include <list>

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

	void SetActive(bool& value);
	bool GetActive() const;

public:

	void AddComponent(GameObject& object);
	void RemoveComponent(GameObject& object);
	void SetComponentActive(GameObject& object);

public:

	void SetShader(std::string shader);
	void SetIsHighlighted(int i);

protected:

	std::list<Component> m_components;

protected:

	bool m_isMovable;
	bool m_isActive;

protected:

	int m_isHighlighted;

protected:

	std::string m_shader;
	std::string m_s;

protected:

	Transform m_transform;

	Buffer m_buffer;
};

#endif