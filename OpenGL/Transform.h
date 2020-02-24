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

	glm::mat4 CalculateLocalToWorldMatrix();

	glm::vec3 GetWorldPos();
	glm::vec3 GetWorldRot();
	glm::vec3 GetWorldScale();

public:

	void AddChild(Transform& transform);
	void DestroyChild(const int& child);
	void DestroyChild(Transform& child);
	void DestroyChildByName(const std::string& child);
	void DestroyChildren();

public:

	glm::mat4 UpdateCoordinates();
	void UpdateChildren();

public:

	void Translate(glm::vec3& pos);;

	void Rotate(float& angle, glm::vec3& axis);

	void Scale(glm::vec3& scale);

public:

	void SetLocalPos(const glm::vec3& pos);
	void SetParent(const Transform& parent);

	void SetLocalCoords(const glm::mat4& mat);

public:

	void SetWorldToLocalCoords(const glm::mat4& mat);
	glm::mat4 GetWorldToLocalCoords()const ;

	glm::mat4 GetLocalCords() const;


	Transform* GetParent() const;
	Transform GetChild(const int& child);
	Transform GetChildByName(const std::string& child);

	int GetChildrenCount() const;

	glm::vec3 GetLocalPos() const;

public:

	GameObject* GetGameObject();

private:

	int m_childrenCount;

private:

	glm::vec3 m_localPos;
	glm::vec3 m_localScale;
	glm::vec3 m_localRotation;

private:

	glm::mat4 m_worldToLocalCoords;
	glm::mat4 m_localToParentCoords;

	const static glm::mat4 s_worldCoords;

private:
	Transform* m_parent; 

	std::list<Transform> m_children;

private:
	
	GameObject* m_object;

private:

	bool isDirty;

	bool isInverseDirty;
};


#endif
  