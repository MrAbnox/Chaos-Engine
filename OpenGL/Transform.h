#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>
#include <list>
#include <string>
#include "Component.h"

class GameObject;
class GameState;

class Transform : public Component
{
private:

	Transform();

public:

	Transform(GameObject* object);
	Transform(GameState* gamestate);
	~Transform() { };

	glm::mat4 operator*(const glm::mat4& second);

public:

	void SetIdentity();
	void SetDirty();

public:

	glm::mat4 calculateLocalToParentMatrix();

public:

	void AddChild(Transform& transform);
	void DestroyChild(const int& child);
	void DestroyChild(Transform& child);
	void DestroyChildByName(const std::string& child);
	void DestroyChildren();

public:

	void UpdateChildren();

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

	void SetLocalPos(const glm::vec3& pos);
	void SetWorldPos(const glm::vec3& pos);
	void SetParent(const Transform& parent);

	void SetWorldCoords(const glm::mat4& value);
	void SetLocalCoords(const glm::mat4& value);
	void SetParentCoords(const glm::mat4& value);

public:

	glm::mat4 GetModel()const ;

	glm::mat4 GetWorldCords() const;
	glm::mat4 GetParentCords() const;
	glm::mat4 GetLocalCords() const;


	Transform* GetParent() const;
	Transform GetChild(const int& child);
	Transform GetChildByName(const std::string& child);

	int GetChildrenCount() const;

	glm::vec3 GetLocalPos() const;
	glm::vec3 GetWorldPos() const;
	GameObject* GetGameObject();

private:

	int m_childrenCount;

private:

	glm::vec3 m_localPos;
	glm::vec3 m_worldPos;

	glm::vec3 m_localAngle;
	glm::vec3 m_worldAngle;

	glm::vec3 m_localScale;
	glm::vec3 m_worldScale;

private:

	glm::mat4 m_model;

	glm::mat4 m_localTransform;
	glm::mat4 m_parentTransform;
	static glm::mat4 s_worldTransform;

private:

	Transform* m_parent; 


private:

	std::list<Transform> m_children;

private:
	
	GameObject* m_object;

private:

	bool isDirty;

	bool isInverseDirty;
};


#endif
  