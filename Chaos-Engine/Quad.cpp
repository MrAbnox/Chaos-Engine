 #include "Quad.h"
#include "TheShader.h"
#include "TheInput.h"

//-------------------------------------------------------------------------------
//Constructor No texture
//-------------------------------------------------------------------------------
Quad::Quad()
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================


	//Set name
	name = "Quad";

	//Set color was white
	glm::vec3 temp_rgb = glm::vec3(1.0f);

	//Set Quad to not textured at all
	isTextured = 0;
	isDoubleTextured = 0;

	//============================================

	//----------------------------- Temp Color array for cube colors

	GLfloat tempColors[]{ temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z };

	//----------------------------- Add temp Colors to Vector

	for (size_t i = 0; i < 12; i++)
	{
		colors.push_back(tempColors[i]);
	}
}

//-------------------------------------------------------------------------------
//Constructor One Texture / Not affected by light
//-------------------------------------------------------------------------------
Quad::Quad(std::string& filepath, std::string textureID)
{

	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================
	//Set color was white
	glm::vec3 temp_rgb = glm::vec3(1.0f);

	//Set name
	name = "Quad";

	//Set Quad to be single textured
	isTextured = 1;
	isDoubleTextured = 0;

	//============================================

	//----------------------------- Temp Color array for cube colors

	GLfloat tempColors[]{ temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z };

	//----------------------------- Add temp Colors to Vector

	for (size_t i = 0; i < 12; i++)
	{
		colors.push_back(tempColors[i]);
	}

	//Load Texture
	texture1.Load(filepath, textureID);
}

//-------------------------------------------------------------------------------
//Constructor Two Textures / Not affected by light
//-------------------------------------------------------------------------------
Quad::Quad(std::string& filepath, std::string& filepath2, std::string textureID, std::string textureID2)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================
	//Set color was white
	glm::vec3 temp_rgb = glm::vec3(1.0f);

	//Set name
	name = "Quad";

	//Set Quad to be single textured
	isTextured = 1;
	isDoubleTextured = 1;

	//============================================

	//----------------------------- Temp Color array for cube colors

	GLfloat tempColors[]{ temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z};

	//----------------------------- Add temp Colors to Vector

	for (size_t i = 0; i < 12; i++)
	{
		colors.push_back(tempColors[i]);
	}

	//Load Textures
	texture1.Load(filepath, textureID);
	texture2.Load(filepath2, textureID2);

}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Quad::~Quad()
{
}

//-------------------------------------------------------------------------------
//OnEnter Function
//-------------------------------------------------------------------------------
void Quad::Create(std::string shaderRef)
{
	//--------------------------------------------
	//Define variables
	//--------------------------------------------

	//============================================
	
	//Set EBO/VAO and VBOs to default
	VAO = 0;
	EBO = 0;
	VBO_color = 0;
	VBO_vertex = 0;

	//Set Position
	position = glm::vec3(0.0f);

	//Set Shininess
	material->SetShine(1.0f);

	//Set programString to pass string
	shader = shaderRef;

	isHighlighted = 1;

	//============================================

	//--------------------------------------------
	//Get Attributes
	//--------------------------------------------

	//Get Attributes from Light Shaders
	if (shader == "Lighting")
	{
		ID_vertex = TheShader::Instance()->GetAttributeID("Lighting_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("Lighting_normalIn");

		isLit = 1;

		if (isTextured == 1)
		{
			ID_texture = TheShader::Instance()->GetAttributeID("Lighting_textureIn");
		}
	}
	else if (shader == "ShadowMapping")
	{
		isLit = 1;

		ID_vertex = TheShader::Instance()->GetAttributeID("ShadowMapping_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("ShadowMapping_normalIn");

		if (isTextured == 1)
		{
			ID_texture = TheShader::Instance()->GetAttributeID("ShadowMapping_textureIn");
		}
	}
	//Get Attributes from Lamp Shaders
	else if (shader == "Lightless")
	{
		ID_color = TheShader::Instance()->GetAttributeID("Lightless_colorIn");
		ID_vertex = TheShader::Instance()->GetAttributeID("Lightless_vertexIn");

		isLit = 0;

		if (isTextured == 1)
		{
			ID_texture = TheShader::Instance()->GetAttributeID("Lightless_textureIn");
		}
	}
	//Get Attributes from LightMap Shaders
	else if (shader == "LightMap")
	{
		ID_normal == TheShader::Instance()->GetAttributeID("LightMap_normalIn");
		ID_vertex = TheShader::Instance()->GetAttributeID("LightMap_vertexIn");

		isLit = 1;

		if (isTextured == 1)
		{
			ID_texture = TheShader::Instance()->GetAttributeID("LightMap_textureIn");
		}
	}
	else if (shader == "Toon")
	{

		isLit = 0;

		ID_vertex = TheShader::Instance()->GetAttributeID("Toon_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("Toon_normalIn");

		if (isTextured == 1)
		{
			ID_texture = TheShader::Instance()->GetAttributeID("Toon_textureIn");
		}
	}
	else if (shader == "NormalMapping")
	{
		isLit = 1;

		ID_vertex = TheShader::Instance()->GetAttributeID("NormalMapping_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("NormalMapping_normalIn");
		ID_texture = TheShader::Instance()->GetAttributeID("NormalMapping_textureIn");
		ID_tangent = TheShader::Instance()->GetAttributeID("NormalMapping_tangentIn");
		ID_bitangent = TheShader::Instance()->GetAttributeID("NormalMapping_bitangentIn");
	}
	else
	{
		TheDebug::Log("Quad is being Created with an unavailable shader, that needs to be overloaded", ALERT);
	}

	//--------------------------------------------
	//Read Files
	//--------------------------------------------

	//Read vertices for Quad
	ReadFile("./Data/Objects/Quad/QuadVertices.txt", VERTICES);

	//Read vertices for Quad
	ReadFile("./Data/Objects/Quad/QuadIndices.txt", INDICES);

	//Read UVs for Quad
	if (isTextured == 1)
	{
		ReadFile("./Data/Objects/Quad/QuadUVs.txt", UVS);
	}

	if (isLit == 1)
	{
		ReadFile("./Data/Objects/Quad/QuadNormals.txt", NORMALS);
	}

	CalculateTangents();

	//--------------------------------------------
	//BUFFERS 
	//--------------------------------------------

	//----------------------------- Bind and get VAO arrays

	buffer->GenerateVertexArrays(1, &VAO);
	buffer->BindVertexArrays(VAO);

	//Fill and link Vertex VBO
	buffer->GenerateBuffers(1, &VBO_vertex);
	buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
	buffer->FillBuffer(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_vertex);

	if (isLit)
	{
		//Fill and link Vertex VBO
		buffer->GenerateBuffers(1, &VBO_normal);
		buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_normal);
		buffer->FillBuffer(GL_ARRAY_BUFFER, normals, GL_STATIC_DRAW);
		buffer->LinkToShader(ID_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);
		buffer->EnableVertexArray(ID_normal);
	}
	else
	{
		//Fill and link color VBO
		buffer->GenerateBuffers(1, &VBO_color);
		buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_color);
		buffer->FillBuffer(GL_ARRAY_BUFFER, colors, GL_STATIC_DRAW);
		buffer->LinkToShader(ID_color, 3, GL_FLOAT, GL_FALSE, 0, 0);
		buffer->EnableVertexArray(ID_color);
	}

	//Check if Quad is textured
	if (isTextured == 1)
	{ 
		//Fill and link texture VBO
		buffer->GenerateBuffers(1, &VBO_texture);
		buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_texture);
		buffer->FillBuffer(GL_ARRAY_BUFFER, UVs, GL_STATIC_DRAW);
		buffer->LinkToShader(ID_texture, 2, GL_FLOAT, GL_FALSE, 0, 0);
		buffer->EnableVertexArray(ID_texture);
	}
	if (hasNormal)
	{
		//Fill and link texture VBO
		buffer->GenerateBuffers(1, &VBO_tangent);
		buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_tangent);
		buffer->FillBuffer(GL_ARRAY_BUFFER, tangents, GL_STATIC_DRAW);
		buffer->LinkToShader(ID_tangent, 3, GL_FLOAT, GL_FALSE, 0, 0);
		buffer->EnableVertexArray(ID_tangent);

		if (hasHeightMap)
		{
			buffer->GenerateBuffers(1, &VBO_bitangent);
			buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_bitangent);
			buffer->FillBuffer(GL_ARRAY_BUFFER, bitangents, GL_STATIC_DRAW);
			buffer->LinkToShader(ID_bitangent, 3, GL_FLOAT, GL_FALSE, 0, 0);
			buffer->EnableVertexArray(ID_bitangent);
		}
	}

	//----------------------------- 
	//EBO
	//-----------------------------

	//Generate Buffer
	buffer->GenerateBuffers(1, &EBO);
	//Bind Buffer
	buffer->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Fill Buffer
	buffer->FillBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW);
	//Bind Vertex Array
	buffer->BindVertexArrays(0);

	//----------------------------- 
	//Send texture information
	//-----------------------------

	if (isLit == 1 && shader != "LightMap" && shader != "Toon")
	{
		TheShader::Instance()->SendUniformData("Lighting_isTextured", isTextured);

		TheShader::Instance()->SendUniformData("Lighting_isDoubleTextured", isDoubleTextured);
	}
	else
	{
		TheShader::Instance()->SendUniformData("Lightless_isTextured", isTextured);
	}
	TheShader::Instance()->SendUniformData("Lighting_textureImage1", 0);
	TheShader::Instance()->SendUniformData("Lighting_textureImage2", 1);
}

//-------------------------------------------------------------------------------
//Update Function
//-------------------------------------------------------------------------------
void Quad::Update()
{
	//---------------------------------------------
	//Send Quads's material data to shader
	//---------------------------------------------

	//Check if Quad is affected by light
	if (shader != "ShadowMapGen" && shader != "ShadowMapping" && shader != "NormalMapping")
	{
		if (isLit == 1)
		{
			//Send material shininess information
			SendShineData();

			//Send material ambient information
			SendAmbientData();

			//Send material specular information
			SendSpecularData();

			//Send material diffuse information
			SendDiffuseData();
		}
	}	


}

//-------------------------------------------------------------------------------
//Draw Function
//-------------------------------------------------------------------------------
void Quad::Draw()
{

	SendModelInformation(shader);

	//Use Shader
	TheShader::Instance()->UseShader(shader.c_str());

	//----------------------------- Check if it is textured

	if (shader != "ShadowMapGen")
	{
		//m_buffer->BindVertexArrays(m_VAO);
		//m_buffer->GenerateBuffers(1, &VBO_vertex);
		//m_buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
		//m_buffer->FillBuffer(GL_ARRAY_BUFFER, m_vertices, GL_STATIC_DRAW);
		//m_buffer->LinkToShader(ID_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//m_buffer->EnableVertexArray(ID_vertex);

		if (isTextured == 1)
		{
			//Make first texture active
			glActiveTexture(GL_TEXTURE0);

			//Bind Texture
			texture1.Bind();

			if (hasNormal)
			{
				//Bind Normal Mapping
				glActiveTexture(GL_TEXTURE1);

				normalMap.Bind();

				if (hasHeightMap)
				{
					//Bind Height Mapping
					glActiveTexture(GL_TEXTURE2);

					heightMap.Bind();
				}
			}

			KeyState keys = TheInput::Instance()->GetKeyStates();

			if (keys[SDL_SCANCODE_O])
			{
				hasNormal = false;
				//m_isToonOn = true;
			}
			else if (keys[SDL_SCANCODE_L])
			{
				hasNormal = true;
				//m_isToonOn = true;
			}
			if (keys[SDL_SCANCODE_M])
			{
				hasHeightMap = false;
			}
			else if (keys[SDL_SCANCODE_P])
			{
				//m_isToonOn = false;
				hasHeightMap = true;
			}
			//glBindTexture(GL_TEXTURE_2D, m_depthMap);
			//----------------------------- Check if it is double textured

			//if (isDoubleTextured == 1)
			//{
			//	//Make second texture active
			//	glActiveTexture(GL_TEXTURE1);

			//	//Bind Second Texture
			//	m_texture2.Bind();
			//}
		}
		//glActiveTexture(GL_TEXTURE2);
		//glBindTexture(GL_TEXTURE_2D, depthMap);
	}
	else
	{
		//m_buffer->BindVertexArrays(m_VAO);
		//m_buffer->GenerateBuffers(1, &VBO_shadowVertex);
		//m_buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_shadowVertex);
		//m_buffer->FillBuffer(GL_ARRAY_BUFFER, m_vertices, GL_STATIC_DRAW);
		//m_buffer->LinkToShader(TheShader::Instance()->GetAttributeID("ShadowMapGen_vertexIn"), 3, GL_FLOAT, GL_FALSE, 0, 0);
		//m_buffer->EnableVertexArray(TheShader::Instance()->GetAttributeID("ShadowMapGen_vertexIn"));
	}
	//----------------------------- Bind Vertex Array And draw cube
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	//----------------------------- Check if it is DoubleTextured, if yes send Uniform Texture information

	//if (isDoubleTextured == 1)
	//{
	//	if (m_shader == "Lighting")
	//	{
	//		TheShader::Instance()->SendUniformData("Lighting_textureImage1", 0);
	//		TheShader::Instance()->SendUniformData("Lighting_textureImage2", 1);
	//	}
	//	else if (m_shader == "LightMap")
	//	{

	//		TheShader::Instance()->SendUniformData("LightMap_material.diffuse", 0);
	//		TheShader::Instance()->SendUniformData("LightMap_material.specular", 1);
	//	}
	//}

	////----------------------------- 
	//if (m_shader == "Toon")
	//{
	//	if (m_material != nullptr)
	//	{
	//		TheShader::Instance()->SendUniformData("Toon_material.color", m_material->GetAmbient());
	//	}
	//	else
	//	{
	//		TheShader::Instance()->SendUniformData("Toon_material.color", glm::vec3(0.0f));
	//	}

	//	TheShader::Instance()->SendUniformData("Toon_toon", m_isHighlighted);
	//	TheShader::Instance()->SendUniformData("Toon_position", v3_position);
	//}
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Quad::Destroy()
{

	//----------------------------- Delete VBOS

	glDeleteBuffers(1, &VBO_vertex);
	glDeleteBuffers(1, &VBO_color);
	glDeleteBuffers(1, &VBO_texture);

	//----------------------------- Delete EBOS

	glDeleteBuffers(1, &EBO);

	//----------------------------- Delete VAOs

	glDeleteVertexArrays(1, &VAO);

	//----------------------------- Delete IDS

	glDisableVertexAttribArray(ID_vertex);
	glDisableVertexAttribArray(ID_color);
	glDisableVertexAttribArray(ID_texture);
	glDisableVertexAttribArray(ID_normal);
}
