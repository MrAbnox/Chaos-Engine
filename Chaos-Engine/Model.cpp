#include <fstream>
#include <iostream>
#include <vector>
#include <gtc\matrix_transform.hpp>     
#include <gtc\type_ptr.hpp> 
#include "Model.h"
#include "TheShader.h"
#include "TheDebug.h"
#include "Texture.h"
#include <stdio.h>
#include <string>
#include <cstring>

std::vector<GLuint> Model::test_indices;
std::vector<glm::vec3> Model::test_normals;
std::vector<glm::vec3> Model::test_vertices;
std::vector<glm::vec2> Model::test_uvs;

//------------------------------------------------------------------------------------------------------
//Constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Model::Model()
{

	m_isTextured = 0;
	m_shininess = 0.1f;

	m_VAO = 0;
	m_EBO = 0;
	m_vertexVBO = 0;
	m_colorVBO = 0;
	m_normalVBO = 0;
	m_textureVBO = 0;
	m_totalVertices = 0;

	m_vertexAttributeID = 0;
	m_normalAttributeID = 0;
	m_textureAttributeID = 0;

}
//------------------------------------------------------------------------------------------------------
//Predicate function that returns flag reference
//------------------------------------------------------------------------------------------------------
GLint& Model::IsTextured()
{

	return m_isTextured;

}
//------------------------------------------------------------------------------------------------------
//Setter function that sets shininess value of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetShininess(GLfloat shininess)
{

	m_shininess = shininess;

}
//------------------------------------------------------------------------------------------------------
//Setter function that sets ambient component of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
{

	m_ambient = glm::vec3(r, g, b);

}
//------------------------------------------------------------------------------------------------------
//Setter function that sets diffuse component of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
{

	m_diffuse = glm::vec3(r, g, b);

}
//------------------------------------------------------------------------------------------------------
//Setter function that sets specular component of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
{

	m_specular = glm::vec3(r, g, b);

}
//------------------------------------------------------------------------------------------------------
//Setter function that sets position of model
//------------------------------------------------------------------------------------------------------
void Model::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{

	m_position = glm::vec3(x, y, z);

}
//------------------------------------------------------------------------------------------------------
//Setter function that sets rotation of model
//------------------------------------------------------------------------------------------------------
void Model::SetRotation(GLfloat x, GLfloat y, GLfloat z)
{

	m_rotation = glm::vec3(x, y, z);

}
//------------------------------------------------------------------------------------------------------
//Setter function that sets scale of model
//------------------------------------------------------------------------------------------------------
void Model::SetScale(GLfloat x, GLfloat y, GLfloat z)
{

	m_scale = glm::vec3(x, y, z);

}


//------------------------------------------------------------------------------------------------------
//Function that loads raw model data from OBJ file 
//------------------------------------------------------------------------------------------------------
bool Model::LoadObj(const std::string& filepath)
{
	std::vector <glm::vec3> m_vertices, m_normals;
	std::vector <glm::vec2> m_uvs;

	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;

	std::vector<unsigned short> out_indices;
	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec2> out_uvs;
	std::vector<glm::vec3> out_normals;

	std::vector<glm::vec3> temp_vertices, temp_normals;
	std::vector<glm::vec2> temp_uvs;

		
	std::string temp_text = "";
	FILE* file = fopen(filepath.c_str(), "r");

	//Open File
	
	if (!file)
	{
		TheDebug::Log("Impossible to openfile", ALERT);
		return false;
	}
	
	//Read file until the end
	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		
		if (res == EOF)
		{
			break;
		}
		
		//Parse lineheader
		int x = strcmp(lineHeader, "v");
		if (strcmp(lineHeader, "v") == 0) 
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		//scan for uvs
		else if (strcmp(lineHeader, "vt") == 0) 
		{
			glm::vec2 uv;
			glm::vec2 uv2;
			glm::vec2 uv3;
			fscanf(file, "%f %f %f %f\n", &uv.x, &uv.y, &uv3.x, &uv2.y);
			temp_uvs.push_back(uv);
		}
		//scan for normals
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		//Scan for faces
		else if (strcmp(lineHeader, "f") == 0) 
		{

			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			
			if (matches != 9)
			{
				printf("File can't be read : ( Try exporting with other options\n");
				fclose(file);
				return false;
			}


			//triangulated
			if (matches == 9)
			{
				//Add 3 total vertices
				m_totalVertices += 3;

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
	}
	std::vector<GLfloat> testVertex;
	std::vector<GLfloat> testUv;
	std::vector<GLfloat> testNormal;

	//Go through each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		m_normals.push_back(normal);

		m_vertices.push_back(vertex);
		m_uvs.push_back(uv);
	}

	fclose(file);
	unsigned short result;

	std::vector<GLuint> indices;
	std::vector<GLuint> testindices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	indexVBO(m_vertices, m_uvs, m_normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	for (size_t i = 0; i < 36; i++)
	{
		testindices.push_back(indices[i]);
	}
	test_vertices = m_vertices;
	test_normals = m_normals;
	test_uvs = m_uvs;
	test_indices = testindices;

	std::vector<GLfloat> testv;
	std::vector<GLfloat> testu;
	std::vector<GLfloat> testn;
	for (size_t i = 0; i < test_vertices.size(); i++)
	{
		testv.push_back(test_vertices[i].x);
		testv.push_back(test_vertices[i].y);
		testv.push_back(test_vertices[i].z);

		testu.push_back(test_uvs[i].x);
		testu.push_back(test_uvs[i].y);

		testn.push_back(test_normals[i].x);
		testn.push_back(test_normals[i].y);
		testn.push_back(test_normals[i].z);

	}
	//Bind all VBOs and shader attributes together with VAO
	//Bind all VBOs and shader attributes together with VAO
	glBindVertexArray(m_VAO);

	//fFll and link vertex VBO
	m_buffer->BindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
	m_buffer->FillBuffer(GL_ARRAY_BUFFER, testv, GL_STATIC_DRAW);
	m_buffer->LinkToShader(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	m_buffer->EnableVertexArray(m_vertexAttributeID);


	//Fill and link texture VBO
	m_buffer->BindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
	m_buffer->FillBuffer(GL_ARRAY_BUFFER, testu, GL_STATIC_DRAW);
	m_buffer->LinkToShader(m_textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	m_buffer->EnableVertexArray(m_textureAttributeID);

	//Fill and link normal VBO
	m_buffer->BindBuffer(GL_ARRAY_BUFFER, m_normalVBO);
	m_buffer->FillBuffer(GL_ARRAY_BUFFER, testn, GL_STATIC_DRAW);
	m_buffer->LinkToShader(m_normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	m_buffer->EnableVertexArray(m_normalAttributeID);

	//Fill EBO with indices 
	m_buffer->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); //gl bind buffer
	m_buffer->FillBuffer(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW); //gl buffer data

	glBindVertexArray(0);
	return true;
}

bool Model::is_near(float v1, float v2) {
	return fabs(v1 - v2) < 0.01f;
}
struct PackedVertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};
bool getSimilarVertexIndex_fast(
	PackedVertex& packed,
	std::map<PackedVertex, unsigned short>& VertexToOutIndex,
	unsigned short& result
) {
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}
// Searches through all already-exported vertices
// for a similar one.
// Similar = same position + same UVs + same normal
bool Model::getSimilarVertexIndex(glm::vec3& in_vertex, glm::vec2& in_uv, glm::vec3& in_normal, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, unsigned short& result)
{
	// Lame linear search
	for (unsigned int i = 0; i < out_vertices.size(); i++)
	{
		if (
			is_near(in_vertex.x, out_vertices[i].x) &&
			is_near(in_vertex.y, out_vertices[i].y) &&
			is_near(in_vertex.z, out_vertices[i].z) &&
			is_near(in_uv.x, out_uvs[i].x) &&
			is_near(in_uv.y, out_uvs[i].y) &&
			is_near(in_normal.x, out_normals[i].x) &&
			is_near(in_normal.y, out_normals[i].y) &&
			is_near(in_normal.z, out_normals[i].z)
			)
		{
			result = i;
			return true;
		}
	}

	// No other vertex could be used instead.
	// Needs to be added to VBO
	return false;
}

void Model::indexVBO_slow(
	std::vector<glm::vec3>& in_vertices,
	std::vector<glm::vec2>& in_uvs,
	std::vector<glm::vec3>& in_normals,

	std::vector<unsigned short>& out_indices,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
) {
	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++) {

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_indices.push_back((unsigned short)out_vertices.size() - 1);
		}
	}
}
void Model::indexVBO(std::vector<glm::vec3>& in_vertices, std::vector<glm::vec2>& in_uvs, std::vector<glm::vec3>& in_normals, std::vector<GLuint>& out_indices, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++) {

		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };


		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}
//------------------------------------------------------------------------------------------------------
//Function that loads raw model data from OBJ file 
//------------------------------------------------------------------------------------------------------
bool Model::LoadModel(const std::string& filename)
{

	//Variables to load and store all model data
	std::fstream file;
	std::string lineText = "";
	unsigned int tokenPosition = 0;

	std::vector<glm::vec3> faceArray;
	std::vector<glm::vec3> vertexArray;
	std::vector<glm::vec2> textureArray;
	std::vector<glm::vec3> normalArray;
	
	std::vector<std::string> subNumbers;
	std::vector<std::string> subStrings;
	
	//Display text to state that file is being opened and read
	std::cout << "Opening and reading model file : " << "\"" << filename << "\"" << std::endl;

	//Open model file
	file.open(filename);

	//If opening of model file failed, display error message
	if (!file)
	{
		TheDebug::Log("File could not be loaded.", ALERT);
		return false;
	}

	//Read in all model data until end of file is reached
	while (!file.eof())
	{

		//Read line of text
		getline(file, lineText);

		//Break text string into smaller substrings
		do
		{
			tokenPosition = lineText.find(' ');
			subStrings.push_back(lineText.substr(0, tokenPosition));
			lineText.erase(0, tokenPosition + 1);
		} while (tokenPosition != std::string::npos);

		//If first token is "v" or "vn", set the vertices and normal values
		if (subStrings[0] == "v" || subStrings[0] == "vn")
		{

			//If it's a vertex position, add it to the vertex array
			if (subStrings[0] == "v")
			{
				vertexArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
				  	                            (GLfloat)(atof(subStrings[2].c_str())),
					                            (GLfloat)(atof(subStrings[3].c_str()))));
			}

			//If it's a normal direction, add it to the normal array
			if (subStrings[0] == "vn")
			{
				normalArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
											    (GLfloat)(atof(subStrings[2].c_str())),
											    (GLfloat)(atof(subStrings[3].c_str()))));
			}

		}

		//If first token is "vt", set the UV data
		if (subStrings[0] == "vt")
		{

			//Add to the textureArray
			textureArray.push_back(glm::vec2((GLfloat)(atof(subStrings[1].c_str())),
				                             (GLfloat)(atof(subStrings[2].c_str()))));

		}

		//If first token is "f", create a new face and set the face data
		if (subStrings[0] == "f")
		{

			//Loop through all three face sub strings 
			for (int i = 1; i <= 3; i++)
			{

				//Break each face substring into three face numeric values
				do
				{
					tokenPosition = subStrings[i].find('/');
					subNumbers.push_back(subStrings[i].substr(0, tokenPosition));
					subStrings[i].erase(0, tokenPosition + 1);
				} while (tokenPosition != std::string::npos);

				//Add to face array
				faceArray.push_back(glm::vec3(atoi(subNumbers[0].c_str()) - 1,
										      atoi(subNumbers[1].c_str()) - 1,
										      atoi(subNumbers[2].c_str()) - 1));

				//Clear numbers for next use
				subNumbers.clear();

			}

		}

		//clear the sub strings for next use
		subStrings.clear();

	}

	//Close model file
	file.close();

	//Display text to state that file has been opened and read
	TheDebug::Log("File opened and read successfully.", SUCCESS);

	//---------------------------------
	//Sift through all data for EBO
	//---------------------------------

	std::vector<GLuint> indices;
	std::vector<Groups> groups;

	//Loop through all triangle faces and individually build vertex groups out of them
	//Then add each vertex group to the array but first check if it's already there and
	//Of it is then skip it but mark EBO to point to that existing index
	//This alleviates the problem of creating a EBO out of OBJ model file data
	for (size_t i = 0; i < faceArray.size(); i++)
	{

		//Create a temporary group
		Groups tri;
		tri.vertex = vertexArray[(const unsigned int)faceArray[i].x];
		tri.texture = textureArray[(const unsigned int)faceArray[i].y];
		tri.normal = normalArray[(const unsigned int)faceArray[i].z];

		//Flag for element found
		bool isFound = false;

		//Set below for-loop starting point to always go 5 elements back
		//So that we don't loop through entire group array each time
		int loopStart = (groups.size() >= 5 ? groups.size() - 5 : 0);

		//Loop through existing groups to see if this group already exists in there
		//And if its found use that index for the EBO otherwise continue searching
		for (size_t j = loopStart; j < groups.size(); j++)
		{
					
			if (tri.vertex == groups[j].vertex &&
				tri.texture == groups[j].texture &&
				tri.normal == groups[j].normal)
			{
				indices.push_back(j);
				isFound = true;
				break;
			}	

		}

		//If nothing was found, it's a new group so add it and index the EBO
		if (!isFound)
		{
			groups.push_back(tri);
			indices.push_back(groups.size() - 1);
		}
	}

	//Stats for vertices saved
	std::cout << "Total Vertices : " << indices.size() << std::endl;
	std::cout << "Actual Vertices : " << groups.size() << std::endl;
	std::cout << "Vertex Space Saved : " 
		      << 100 - (int)((float)(groups.size()) / (float)(indices.size()) * 100) << "%" << std::endl;

	//---------------------------------
	//Add all data to VBOs
	//---------------------------------

	//Storage for our vertex, texture and normal data
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> textures;
	std::vector<GLfloat> normals;

	//Add all vertex, texture and normal data to the main vectors
	//From here this data will be fed into to VBO later on
	for (size_t j = 0; j < groups.size(); j++)
	{
		
		vertices.push_back(groups[j].vertex.x);
		vertices.push_back(groups[j].vertex.y);
		vertices.push_back(groups[j].vertex.z);

		textures.push_back(groups[j].texture.s);
		textures.push_back(groups[j].texture.t);

		normals.push_back(groups[j].normal.x);
		normals.push_back(groups[j].normal.y);
		normals.push_back(groups[j].normal.z);

	}

	//Total up vertices for use in Draw() function
	m_totalVertices = indices.size();

	std::vector<GLfloat> testv;
	std::vector<GLfloat> testu;
	std::vector<GLfloat> testn;
	std::vector<unsigned int> testi;
	for (size_t i = 0; i < test_vertices.size(); i++)
	{
		testv.push_back(test_vertices[i].x);
		testv.push_back(test_vertices[i].y);
		testv.push_back(test_vertices[i].z);

		testu.push_back(test_uvs[i].x);
		testu.push_back(test_uvs[i].y);

		testn.push_back(test_normals[i].x);
		testn.push_back(test_normals[i].y);
		testn.push_back(test_normals[i].z);

		testi.push_back(test_indices[i]);
	}

	if (testv == vertices)
	{
		TheDebug::Log("HOLY MOLY", ALERT);
	}
	if (testu == textures)
	{
		TheDebug::Log("HOLY MOLY", ALERT);
	}
	if (testn == normals)
	{
		TheDebug::Log("HOLY MOLY", ALERT);
	}

	if (testi == indices)
	{
		TheDebug::Log("HOLY MOLY", ALERT);
	}
	//Bind all VBOs and shader attributes together with VAO
	glBindVertexArray(m_VAO);

		//fFll and link vertex VBO
		m_buffer->BindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
		m_buffer->FillBuffer(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
		m_buffer->LinkToShader(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		m_buffer->EnableVertexArray(m_vertexAttributeID);


		//Fill and link texture VBO
		m_buffer->BindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
		m_buffer->FillBuffer(GL_ARRAY_BUFFER, textures, GL_STATIC_DRAW);
		m_buffer->LinkToShader(m_textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
		m_buffer->EnableVertexArray(m_textureAttributeID);

		//Fill and link normal VBO
		m_buffer->BindBuffer(GL_ARRAY_BUFFER, m_normalVBO);
		m_buffer->FillBuffer(GL_ARRAY_BUFFER, normals, GL_STATIC_DRAW);
		m_buffer->LinkToShader(m_normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		m_buffer->EnableVertexArray(m_normalAttributeID);

		//Fill EBO with indices 
		m_buffer->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		m_buffer->FillBuffer(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	return true;

}
//------------------------------------------------------------------------------------------------------
//Function that loads in texture file for cube
//------------------------------------------------------------------------------------------------------
bool Model::LoadTexture(const std::string& filename, const std::string textureID)
{
	m_isTextured = 1;

	return m_texture.Load(filename, textureID);
}
//------------------------------------------------------------------------------------------------------
//Function that unloads texture file for cube
//------------------------------------------------------------------------------------------------------
void Model::UnloadTexture(const std::string textureID)
{
	m_isTextured = 0;

	m_texture.Unload(textureID);
}
//------------------------------------------------------------------------------------------------------
//Function that creates and fills all buffers with vertex and color data 
//------------------------------------------------------------------------------------------------------
void Model::Create(std::string programString)
{
	//Set program string to classe's
	m_shader = programString;

	//Make sure model always exists
	m_scale = glm::vec3(1.0f);

	//Set material color to default
	m_shininess = 1.0f;
	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);

	m_isHighlighted = 1;

	//Get all other shader IDs relating to attributes
	if (m_shader == "Lighting")
	{
		m_vertexAttributeID = TheShader::Instance()->GetAttributeID("Lighting_vertexIn");
		m_normalAttributeID = TheShader::Instance()->GetAttributeID("Lighting_normalIn");
		m_textureAttributeID = TheShader::Instance()->GetAttributeID("Lighting_textureIn");
	}
	else if (m_shader == "ShadowMapping")
	{
		m_vertexAttributeID = TheShader::Instance()->GetAttributeID("ShadowMapping_vertexIn");
		m_normalAttributeID = TheShader::Instance()->GetAttributeID("ShadowMapping_normalIn");
		m_textureAttributeID = TheShader::Instance()->GetAttributeID("ShadowMapping_textureIn");
	}
	else if (m_shader == "Lightless")
	{
		m_vertexAttributeID = TheShader::Instance()->GetAttributeID("Lightless_vertexIn");
		m_textureAttributeID = TheShader::Instance()->GetAttributeID("Lightless_textureIn");
	}
	else if (m_shader == "Toon")
	{
		m_vertexAttributeID = TheShader::Instance()->GetAttributeID("Toon_vertexIn");
		m_normalAttributeID = TheShader::Instance()->GetAttributeID("Toon_normalIn");
		m_textureAttributeID = TheShader::Instance()->GetAttributeID("Toon_normalIn");
	}

	//Create VAO, VBOs and EBO
	m_buffer->GenerateVertexArrays(1, &m_VAO);
	m_buffer->GenerateBuffers(1, &m_vertexVBO);
	m_buffer->GenerateBuffers(1, &m_colorVBO);
	m_buffer->GenerateBuffers(1, &m_normalVBO);
	m_buffer->GenerateBuffers(1, &m_textureVBO);
	m_buffer->GenerateBuffers(1, &m_EBO);
}
//------------------------------------------------------------------------------------------------------
//Function that adjusts model's transformations
//------------------------------------------------------------------------------------------------------
void Model::Update()
{
	////Set model and normal matrices to identity
	//m_normal = glm::mat3(1.0f);


	////Apply all transformations to model matrix
	////Translate(m_position);

	//Rotate(glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0));
	//Rotate(glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0));
	//Rotate(glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0));

	//Scale(m_scale);

	////Convert model matrix to 3x3 and invert it for normals to use in shader
	//m_normal = glm::inverse(glm::mat3(m_transform->GetLocalToWorldCoords()));

}
//------------------------------------------------------------------------------------------------------
//Function that renders model on screen
//------------------------------------------------------------------------------------------------------
void Model::Draw()
{
	if (m_shader == "Lighting")
	{
		//Send model matrix to vertex shader
		TheShader::Instance()->SendUniformData("Lighting_model", 1, GL_FALSE, m_transform->GetLocalToWorldCoords());

		//Send normal matrix to vertex shader  ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CHECK WITH KARSTEN
		glUniformMatrix3fv(m_normalAttributeID, 1, GL_TRUE, &m_normal[0][0]);

		TheShader::Instance()->SendUniformData("Lighting_material.ambient", 1, &m_ambient.r);
		TheShader::Instance()->SendUniformData("Lighting_material.diffuse", 1, &m_diffuse.r);
		TheShader::Instance()->SendUniformData("Lighting_material.specular", 1, &m_specular.r);
		TheShader::Instance()->SendUniformData("Lighting_material.shininess", m_shininess);

		TheShader::Instance()->SendUniformData("Lighting_isTextured", m_isTextured);
	}
	else if (m_shader == "Lightless")
	{
		//Send model matrix to vertex shader
		TheShader::Instance()->SendUniformData("Lightless_model", 1, GL_FALSE, m_transform->GetLocalToWorldCoords());
		TheShader::Instance()->SendUniformData("Lightless_isTextured", m_isTextured);
	}
	else if (m_shader == "ShadowMapping")
	{
		TheShader::Instance()->SendUniformData("ShadowMapping_model", 1, GL_FALSE, m_transform->GetLocalToWorldCoords());
	}
	else if (m_shader == "ShadowMapGen")
	{
		TheShader::Instance()->SendUniformData("ShadowMapGen_model", 1, GL_FALSE, m_transform->GetLocalToWorldCoords());
	}
	else if (m_shader == "Toon")
	{
		glm::vec3 v3_rgb = glm::vec3(0.0f);
		glm::vec3 v3_position = glm::vec3(0.0f);

		TheShader::Instance()->SendUniformData("Toon_model", 1, GL_FALSE, m_transform->GetLocalToWorldCoords());
		TheShader::Instance()->SendUniformData("Toon_material.ambient", 1, &m_ambient.r);
		TheShader::Instance()->SendUniformData("Toon_material.diffuse", 1, &m_diffuse.r);
		TheShader::Instance()->SendUniformData("Toon_toon", m_isHighlighted);
		TheShader::Instance()->SendUniformData("Toon_material.color", v3_rgb);
		TheShader::Instance()->SendUniformData("Toon_position", v3_position);

	}

	//Only if model is set to be textured bind the texture
	if(m_isTextured == 1)
	{
		glActiveTexture(GL_TEXTURE0);
		m_texture.Bind();
	}

	//Bind VAO and render everything!
	glBindVertexArray(m_VAO);

		glDrawElements(GL_TRIANGLES, test_indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

}
//------------------------------------------------------------------------------------------------------
//Function that destroys all buffer objects
//------------------------------------------------------------------------------------------------------
void Model::Destroy()
{

	//destroy EBO, VBOs and VAO
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_textureVBO);
	glDeleteBuffers(1, &m_normalVBO);
	glDeleteBuffers(1, &m_colorVBO);
	glDeleteBuffers(1, &m_vertexVBO);
	glDeleteVertexArrays(1, &m_VAO);

}
