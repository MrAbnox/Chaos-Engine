#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Buffer.h"
#include "Transform.h"
#include "Component.h"
#include "glad.h"
#include "TheDebug.h"
#include <glm.hpp>
#include <list>

class GameObject
{

public:

	GameObject();
	~GameObject() {};

public:

	virtual void Create() {};
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

public:

	void SendModelInformation(const std::string shader);
	void SetIdentity();

public:

	void UpdateChildren();

public:

	void Translate(const glm::vec3 v3); 

	void Rotate(const float angle, const glm::vec3 v3);

	void Scale(const glm::vec3 v3);

public:

	void SetIsEnabled(const bool& value);
	bool GetIsEnabled() const;

public:

	int GetChildrenCount() const;

public:

	Transform GetTransform() const;

public:

	void AddComponent(Component& component);
	void RemoveComponent(Component& component);
	void SetComponentActive(Component& component, bool& value);

public:

	std::string GetShader() const;

	void SetShader(std::string shader);
	void SetIsHighlighted(int i);

protected:

	std::list<Component> m_components;

protected:

	bool m_isMovable;
	bool m_isEnabled;

protected:

	int m_isHighlighted;

protected:

	std::string m_shader;
	std::string m_s;

protected:

	Transform* m_transform;

	Buffer m_buffer;

protected:

	bool canSendCoords;
};

#endif