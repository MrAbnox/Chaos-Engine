#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Buffer.h"
#include "Material.h"
#
#include "Transform.h"
#include "Component.h"
#include "glad/glad.h"
#include "TheDebug.h"
#include <glm.hpp>
#include <list>

enum Components 
{
	MATERIAL,
	BUFFER,
	RENDERER,
	TRANSFORM
};

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

	std::string Getname() const;

public:

	void SetIsEnabled(const bool& value);
	bool GetIsEnabled() const;

public:

	int GetChildrenCount() const;

public:

	Transform* GetTransform() const;


public:

	void AddComponent(Components component);

public:

	Buffer* GetBuffer() const;
	Material* GetMaterial() const;

public:

	bool GetHasPhong() const;

public:

	std::string GetShader() const;

public:

	void SetShader(std::string shader);
	void SetIsHighlighted(int i);

protected:

	bool m_isMovable;
	bool m_isEnabled;
	bool m_hasPhong;

protected:

	int m_isHighlighted;

protected:

	std::string m_shader;
	std::string m_name;

protected:

	Buffer* m_buffer;
	Material* m_material;
	Transform* m_transform;
};

#endif