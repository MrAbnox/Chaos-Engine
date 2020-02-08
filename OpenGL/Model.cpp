#include <fstream>
#include <iostream>
#include <vector>
#include <gtc\matrix_transform.hpp>     
#include <gtc\type_ptr.hpp> 
#include "Model.h"
#include "TheShader.h"
#include "Texture.h"

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

	//Bind all VBOs and shader attributes together with VAO
	glBindVertexArray(m_VAO);

		//fFll and link vertex VBO
		m_buffer.BindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
		m_buffer.FillBuffer(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
		m_buffer.LinkToShader(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		m_buffer.EnableVertexArray(m_vertexAttributeID);


		//Fill and link texture VBO
		m_buffer.BindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
		m_buffer.FillBuffer(GL_ARRAY_BUFFER, textures, GL_STATIC_DRAW);
		m_buffer.LinkToShader(m_textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
		m_buffer.EnableVertexArray(m_textureAttributeID);

		//Fill and link normal VBO
		m_buffer.BindBuffer(GL_ARRAY_BUFFER, m_normalVBO);
		m_buffer.FillBuffer(GL_ARRAY_BUFFER, normals, GL_STATIC_DRAW);
		m_buffer.LinkToShader(m_normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		m_buffer.EnableVertexArray(m_normalAttributeID);

		//Fill EBO with indices 
		m_buffer.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		m_buffer.FillBuffer(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

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
	m_buffer.GenerateVertexArrays(1, &m_VAO);
	m_buffer.GenerateBuffers(1, &m_vertexVBO);
	m_buffer.GenerateBuffers(1, &m_colorVBO);
	m_buffer.GenerateBuffers(1, &m_normalVBO);
	m_buffer.GenerateBuffers(1, &m_textureVBO);
	m_buffer.GenerateBuffers(1, &m_EBO);
}
//------------------------------------------------------------------------------------------------------
//Function that adjusts model's transformations
//------------------------------------------------------------------------------------------------------
void Model::Update()
{

	//Set model and normal matrices to identity
	m_normal = glm::mat3(1.0f);


	//Apply all transformations to model matrix
	Translate(m_position);

	Rotate(glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0));
	Rotate(glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0));
	Rotate(glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0));

	Scale(m_scale);


	//Convert model matrix to 3x3 and invert it for normals to use in shader
	m_normal = glm::inverse(glm::mat3(m_transform.GetModel()));

}
//------------------------------------------------------------------------------------------------------
//Function that renders model on screen
//------------------------------------------------------------------------------------------------------
void Model::Draw()
{
	if (m_shader == "Lighting")
	{
		//Send model matrix to vertex shader
		TheShader::Instance()->SendUniformData("Lighting_model", 1, GL_FALSE, m_transform.GetModel());

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
		TheShader::Instance()->SendUniformData("Lightless_model", 1, GL_FALSE, m_transform.GetModel());
		TheShader::Instance()->SendUniformData("Lightless_isTextured", m_isTextured);
	}
	else if (m_shader == "Toon")
	{
		glm::vec3 v3_rgb = glm::vec3(0.0f);
		glm::vec3 v3_position = glm::vec3(0.0f);

		TheShader::Instance()->SendUniformData("Toon_model", 1, GL_FALSE, m_transform.GetModel());
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

		glDrawElements(GL_TRIANGLES, m_totalVertices, GL_UNSIGNED_INT, 0);

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