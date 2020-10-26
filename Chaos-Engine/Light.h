#ifndef LIGHTS_H
#define LIGHTS_H

#include "GameObject.h"
#include <glm.hpp>
#include <fstream>
#include "Box.h"
#include "ShadowInfo.h"

enum Lights
{
	SPOTLIGHT,
	POINTLIGHT,
	DIRECTIONALLIGHT
};

class Light : public GameObject
{
public:

	Light();
	Light(const Lights lightRef);
	~Light() { delete shadowInfo; };

public:

	void Create() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

public:

	void Reset();
	void SendInfo();

public:

	static void OpenConfigurations();

public:
	
	void SetAmbient(glm::vec3 v3);
	void SetAmbient(float x, float y, float z);

	void SetDiffuse(glm::vec3 v3);
	void SetDiffuse(float x, float y, float z);

	void SetSpecular(glm::vec3 v3);
	void SetSpecular(float x, float y, float z);

	void SetPos(const glm::vec3 v3);
	void SetPos(const float x, const float y, const float z);

	void SetDirection(const glm::vec3 v3);
	void SetDirection(const float x, const float y, const float z);

public:

	ShadowInfo* GetShadowInfo();
	void SetShadowInfo(ShadowInfo* shadowinfo);

private:

	GLfloat pointSize;

private:

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 rgb;

private:

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;

private:

	int lightNumber;

private:

	Lights light;

private:

	std::vector<std::string> lightInformation;

private:

	static std::map<std::string, float> lightValues;

private:

	static int numberPointLights;
	static int numberSpotLights;
	static int directionalLightNumber;
	static bool hasReadConfigFile;

private:

	GLuint VAO;

private:

	ShadowInfo* shadowInfo;
};

#endif