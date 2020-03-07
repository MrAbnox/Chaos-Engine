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
