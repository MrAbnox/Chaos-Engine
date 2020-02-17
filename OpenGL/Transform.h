#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>
#include <list>
#include <string>
#include "Component.h"

class Transform : public Component
{

public:

	Transform();
	~Transform() { };

	glm::mat4 operator*(const glm::mat4& second);

public:

	void SetIdentity();

public:

	void Translate(glm::vec3& v3);
	void Translate(glm::vec2& v2, float& z);
	void Translate(float& x, float& y, float& z);

	void Rotate(float& angle, glm::vec3& v3);
	void Rotate(float& angle, glm::vec2& v2, float& z);
	void Rotate(float& angle, float& x, float& y, float& z);

	void Scale(glm::vec3& v3);
	void Scale(glm::vec2& v2, float& z);
	void Scale(float& x, float& y, float& z);

public:

	void AddChild(const Transform& transform);
	void DestroyChild(const int& child);
	void DestroyChildByName(const std::string& child);

public:

	glm::mat4 GetModel();
	Transform GetParent() const;
	Transform GetChild(const int& child);
	Transform GetChildByName(const std::string& child);
	int GetChildrenCount() const;
	glm::vec3 GetLocalPos() const;
	glm::vec3 GetWorldPos() const;
	//GameObject GetGameObject() const;

public:

	void SetLocalPos(const glm::vec3& pos);
	void SetWorldPos(const glm::vec3& pos);
	void SetParent(const Transform& parent);

private:

	int m_childrenCount;

private:

	glm::vec3 m_localPos;
	glm::vec3 m_worldPos;

private:

	glm::mat4 m_model;

private:

	std::list<Transform> m_children;

private:
	
	//GameObject* object;
};


#endif
  