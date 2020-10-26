#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>
#include <list>
#include <string>
#include "Component.h"

class GameObject;

class Transform : public Component
{
private:

	Transform();

public:

	Transform(GameObject* object);
	~Transform();

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

	void AddChild(Transform& tempTransform);
	void DestroyChild(const int& child);
	void DestroyChild(Transform& child);
	void DestroyChildByName(const std::string& child);
	void DestroyChildren();

public:

	void UpdateCoordinates();
	void UpdateChildren();

public:

	void Translate(glm::vec3& pos);;
	void Rotate(float& angle, glm::vec3& axis);
	void Scale(glm::vec3& scale);

public:

	void SetNotDirty();

public:

	void SetLocalPos(const glm::vec3& pos);
	void SetLocalRot(const glm::vec3& rot);

	void SetLocalCoords(const glm::mat4& mat);
	void SetLocalToWorldCoords(const glm::mat4& mat);

public:

	glm::vec3 GetLocalPos() const;
	glm::vec3 GetLocalRot();
	glm::vec3 GetLocalScale() const;

	glm::mat4 GetLocalCords() const;
	glm::mat4 GetLocalToWorldCoords();

public:

	void SetParent(const Transform& parentRef);

public:

	Transform* GetParent() const;
	Transform GetChild(const int& child);
	Transform GetChildByName(const std::string& child);

	int GetChildrenCount() const;

public:

	void SetGameObject(GameObject& objectRef);
	GameObject* GetGameObject();

private:

	int childrenCount;

private:

	glm::vec3 localPos;
	glm::vec3 localScale;
	glm::vec3 localRotation;

private:

	glm::mat4 localToWorldCoords;
	glm::mat4 localToParentCoords;

	const static glm::mat4 worldCoords;

private:

	Transform* parent; 

	std::list<Transform> children;

private:
	
	GameObject* object;

private:

	bool isDirty;

	bool isInverseDirty;
};


#endif
  