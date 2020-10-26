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
#include "AABB.h"
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
	~GameObject();

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
	void UpdateTriangles();

public:

	void SetDepthMap(unsigned int depthmap);

	void Translate(const glm::vec3 v3); 
	void Rotate(const float angle, const glm::vec3 v3);
	void Scale(const glm::vec3 v3);

public:

	void SetName(std::string nameRef);
	std::string Getname() const;

public:

	void SetIsEnabled(const bool& value);
	bool GetIsEnabled() const;

public:

	int GetChildrenCount() const;

public:

	Transform* GetTransform() const;
	const AABB& GetCollider() { return collider; }

public:

	void AddComponent(Components component);

public:

	Buffer* GetBuffer() const;
	Material* GetMaterial();

public:

	bool GetHasPhong() const;

public:

	std::string GetShader() const;

public:

	void SetShader(std::string shader);
	void SetIsHighlighted(int i);

protected:

	void UpdateCollider();

protected:

	bool isMovable;
	bool isEnabled;
	bool hasPhong;

protected:

	int isHighlighted;

protected:

	std::string shader;
	std::string name;

protected:

	Buffer* buffer;
	Material* material;
	Transform* transform;
	GLuint VAO;

	unsigned int depthMap;

	AABB collider;
};

#endif