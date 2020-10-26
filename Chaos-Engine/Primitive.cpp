#include "Primitive.h"
#include "Tools.h"
#include "TheDebug.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Primitive::Primitive()
{
	hasPhong = true;

	AddComponent(BUFFER);
	AddComponent(MATERIAL);
}

//-------------------------------------------------------------------------------
//Read File function
//-------------------------------------------------------------------------------
void Primitive::ReadFile(std::string filepath, Files f)
{
	//Declare token
	token = ',';

	//----------------------------------------------------------
	//Open text file and check object's data
	//----------------------------------------------------------

	switch (f)
	{
	case Primitive::INDICES:

		//Open Text file
		indicesStream.open(filepath, std::ios_base::in);

		//Check if file is Open
		if (indicesStream.is_open())
		{

			//Loop until text file is fully read
			while (!indicesStream.eof())
			{
				//Create temporary string and store corresponsive line
				std::string textString;
				std::getline(indicesStream, textString);

				//Parse each line
				ParseText(textString, token, indices);
			}
		}
		else
		{
			TheDebug::Log("Could not open Indices stream", ALERT);
		}

		break;

	case Primitive::VERTICES:

		//Open Text file

		verticesStream.open(filepath, std::ios_base::in);

		if (verticesStream.is_open())
		{
			//Loop until text file is fully read
			while (!verticesStream.eof())
			{
				//Create temporary string and store corresponsive line

				std::string textString;
				std::getline(verticesStream, textString);

				//Parse each line
				ParseText(textString, token, vertices);
			}
		}
		else
		{
			TheDebug::Log("Could not open Vertices stream", ALERT);
		}

		break;

	case Primitive::UVS:

		//Open Text file
		textureUVsStream.open(filepath, std::ios_base::in);

		if (textureUVsStream.is_open())
		{
			//Loop until text file is fully read
			while (!textureUVsStream.eof())
			{
				//Create temporary string and store corresponsive line

				std::string textString;
				std::getline(textureUVsStream, textString);

				//Parse each line
				ParseText(textString, token, UVs);
			}
		}
		else
		{
			TheDebug::Log("Could not open UVs stream", ALERT);
		}

		break;

	case Primitive::NORMALS:

		//Open Text file
		normalsStream.open(filepath, std::ios_base::in);

		if (normalsStream.is_open())
		{
			//Loop until text file is fully read
			while (!normalsStream.eof())
			{
				//Create temporary string and store corresponsive line
				std::string textString;
				std::getline(normalsStream, textString);

				//Parse each line
				ParseText(textString, token, normals);
			}
		}
		else
		{
			TheDebug::Log("Could not open normals stream text file", ALERT);
		}

		break;

	default:

		break;
	}
}

//-------------------------------------------------------------------------------
//Send Material Shininess information
//-------------------------------------------------------------------------------
void Primitive::SendShineData()
{
	material->SendData(Materials::M_SHINE, shader);
}

//-------------------------------------------------------------------------------
//Send Material Ambient information
//-------------------------------------------------------------------------------
void Primitive::SendAmbientData()
{
	material->SendData(Materials::M_AMBIENT, shader);
}

//-------------------------------------------------------------------------------
//Send Material Diffuse information
//-------------------------------------------------------------------------------
void Primitive::SendDiffuseData()
{
	material->SendData(Materials::M_DIFFUSE, shader);
}

//-------------------------------------------------------------------------------
//Send Material Specular information
//-------------------------------------------------------------------------------
void Primitive::SendSpecularData()
{
	material->SendData(Materials::M_SPECULAR, shader);
}

//-------------------------------------------------------------------------------
//Set Buffer Dirty
//-------------------------------------------------------------------------------
void Primitive::SetBufferDirty()
{
	isBufferDirty = true;
}

//-------------------------------------------------------------------------------
//SetIsLit
//-------------------------------------------------------------------------------
void Primitive::SetIsLit(int x)
{
	isLit = x;
}
//-------------------------------------------------------------------------------
//Set normal Map
//-------------------------------------------------------------------------------
void Primitive::SetNormalMap(std::string filepath)
{
	hasNormal = true;
	std::string tempSave = filepath;
	std::vector<std::string> tempVec;
	char tempToken = '/';
	ParseText(tempSave, tempToken, tempVec);
	normalMap.Load(filepath, tempVec[1]);
}

void Primitive::SetHeightMap(std::string filepath)
{
	hasHeightMap = true;
	std::string tempSave = filepath;
	std::vector<std::string> tempVec;
	char tempToken = '/';
	ParseText(tempSave, tempToken, tempVec);
	heightMap.Load(filepath, tempVec[1]);
}

//-------------------------------------------------------------------------------
//Calculate Tangents
//-------------------------------------------------------------------------------
void Primitive::CalculateTangents()
{
	// positions
	glm::vec3 pos1(vertices[0], vertices[1], vertices[2]);
	glm::vec3 pos2(vertices[3], vertices[4], vertices[5]);
	glm::vec3 pos3(vertices[6], vertices[7], vertices[8]);
	glm::vec3 pos4(vertices[9], vertices[10], vertices[11]);
	// texture coordinates
	glm::vec2 uv1(0.0f, 1.0f);
	glm::vec2 uv2(0.0f, 0.0f);
	glm::vec2 uv3(1.0f, 0.0f);
	glm::vec2 uv4(1.0f, 1.0f);
	// normal vector
	glm::vec3 nm(0.0f, 0.0f, 1.0f);

	// calculate tangent/bitangent vectors of both triangles
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;

	// triangle 1
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent1 = glm::normalize(tangent1);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent1 = glm::normalize(bitangent1);

	for (size_t i = 0; i < 3; i++)
	{
		tangents.push_back(tangent1.x);
		tangents.push_back(tangent1.y);
		tangents.push_back(tangent1.z);

		bitangents.push_back(bitangent1.x);
		bitangents.push_back(bitangent1.y);
		bitangents.push_back(bitangent1.z);
	}

	// triangle 2
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent2 = glm::normalize(tangent2);

	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent2 = glm::normalize(bitangent2);

	for (size_t i = 0; i < 3; i++)
	{
		tangents.push_back(tangent2.x);
		tangents.push_back(tangent2.y);
		tangents.push_back(tangent2.z);

		bitangents.push_back(bitangent2.x);
		bitangents.push_back(bitangent2.y);
		bitangents.push_back(bitangent2.z);
	}
}
