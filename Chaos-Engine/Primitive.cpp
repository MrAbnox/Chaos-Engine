#include "Primitive.h"
#include "Tools.h"
#include "TheDebug.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Primitive::Primitive()
{
	m_hasPhong = true;

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
		m_indicesStream.open(filepath, std::ios_base::in);

		//Check if file is Open
		if (m_indicesStream.is_open())
		{

			//Loop until text file is fully read
			while (!m_indicesStream.eof())
			{

				//----------------------------- Create temporary string and store corresponsive line

				std::string textString;
				std::getline(m_indicesStream, textString);

				//Parse each line
				ParseText(textString, token, m_indices);
			}
		}
		else
		{
			TheDebug::Log("Could not open Indices stream", ALERT);
		}

		break;


	case Primitive::VERTICES:

		//----------------------------- Open Text file

		m_verticesStream.open(filepath, std::ios_base::in);

		if (m_verticesStream.is_open())
		{

			//----------------------------- Loop until text file is fully read

			while (!m_verticesStream.eof())
			{

				//----------------------------- Create temporary string and store corresponsive line

				std::string textString;
				std::getline(m_verticesStream, textString);

				//Parse each line
				ParseText(textString, token, m_vertices);
			}
		}
		else
		{
			TheDebug::Log("Could not open Vertices stream", ALERT);
		}

		break;


	case Primitive::UVS:

		//----------------------------- Open Text file

		m_textureUVsStream.open(filepath, std::ios_base::in);

		if (m_textureUVsStream.is_open())
		{

			//----------------------------- Loop until text file is fully read

			while (!m_textureUVsStream.eof())
			{

				//----------------------------- Create temporary string and store corresponsive line

				std::string textString;
				std::getline(m_textureUVsStream, textString);

				//Parse each line
				ParseText(textString, token, m_UVs);
			}
		}
		else
		{
			TheDebug::Log("Could not open UVs stream", ALERT);
		}

		break;

	case Primitive::NORMALS:

		//Open Text file
		m_normalsStream.open(filepath, std::ios_base::in);

		if (m_normalsStream.is_open())
		{

			//Loop until text file is fully read
			while (!m_normalsStream.eof())
			{

				//----------------------------- Create temporary string and store corresponsive line

				std::string textString;
				std::getline(m_normalsStream, textString);

				//Parse each line
				ParseText(textString, token, m_normals);
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
	m_material->SendData(M_SHINE, m_shader);
}

//-------------------------------------------------------------------------------
//Send Material Ambient information
//-------------------------------------------------------------------------------
void Primitive::SendAmbientData()
{
	m_material->SendData(M_AMBIENT, m_shader);
}

//-------------------------------------------------------------------------------
//Send Material Diffuse information
//-------------------------------------------------------------------------------
void Primitive::SendDiffuseData()
{
	m_material->SendData(M_DIFFUSE, m_shader);
}

//-------------------------------------------------------------------------------
//Send Material Specular information
//-------------------------------------------------------------------------------
void Primitive::SendSpecularData()
{
	m_material->SendData(M_SPECULAR, m_shader);
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
	m_isLit = x;
}

//-------------------------------------------------------------------------------
//Calculate Tangent and bitangent
//-------------------------------------------------------------------------------
void Primitive::CalculateTangents()
{
	// positions
	glm::vec3 pos1(m_vertices[0], m_vertices[1], m_vertices[2]);
	glm::vec3 pos2(m_vertices[3], m_vertices[4], m_vertices[5]);
	glm::vec3 pos3(m_vertices[6], m_vertices[7], m_vertices[8]);
	glm::vec3 pos4(m_vertices[9], m_vertices[10], m_vertices[11]);
	// texture coordinates
	glm::vec2 uv1(0.0f, 1.0f);
	glm::vec2 uv2(0.0f, 0.0f);
	glm::vec2 uv3(1.0f, 0.0f);
	glm::vec2 uv4(1.0f, 1.0f);
	// normal vector
	glm::vec3 nm(0.0f, 0.0f, 1.0f);

	// calculate tangent/bitangent vectors of both triangles
	glm::vec3 tangent1;
	glm::vec3 tangent2;
	// triangle 1
	// ----------
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent1 = glm::normalize(tangent1);


	for (size_t i = 0; i < 3; i++)
	{
		m_tangents.push_back(tangent1.x);
		m_tangents.push_back(tangent1.y);
		m_tangents.push_back(tangent1.z);
	}

	// triangle 2
	// ----------
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent2 = glm::normalize(tangent2);

	for (size_t i = 0; i < 3; i++)
	{
		m_tangents.push_back(tangent2.x);
		m_tangents.push_back(tangent2.y);
		m_tangents.push_back(tangent2.z);
	}
}


