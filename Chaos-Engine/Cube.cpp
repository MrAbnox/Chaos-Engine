#include "Cube.h"
#include "TheShader.h"
#include "Tools.h"
#include "TheInput.h"

Texture Cube::skyBoxTexture;
//-------------------------------------------------------------------------------
//Constructor No texture
//-------------------------------------------------------------------------------
Cube::Cube(std::string shaderRef)
{	
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//Set Cube
	name = "Cube";

	//Set cube to not textured at all
	isTextured = 0;
	isDoubleTextured = 0;

	//Check if object is Lit 
	if (shaderRef == "Lighting")
	{
		isLit = true;
	}
	else
	{
		isLit = false;
	}

	//Set Cube to not mapped (This variable is only on for the proper cube Mapping)
	isCubeMapped = false;

	isTextured = false;;

	//Set color was white
	glm::vec3 temp_rgb = glm::vec3(1.0f);

	//Temp Color array for cube colors
	GLfloat tempColors[]{ temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face1 front
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
								
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 back
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
									
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 left
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
								
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 right
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
								
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 top
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
									
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 bottom
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z
	};

	//Add temp Colors to Vector

	for (size_t i = 0; i < 72; i++)
	{
		colors.push_back(tempColors[i]);
	}
}

//-------------------------------------------------------------------------------
//Constructor One Texture / not affected by light
//-------------------------------------------------------------------------------
Cube::Cube(bool isCubeMapped, std::string filepath, std::string textureID)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//Set color was white
	glm::vec3 temp_rgb = glm::vec3(1.0f);

	//Set cube to single textured
	isTextured = 1;
	isDoubleTextured = 0;

	//Set Cube to not mapped (This variable is only on for the proper cube Mapping)
	isCubeMapped = false;

	//Temp Color array for cube colors
	GLfloat tempColors[]{ temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face1 front
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
								
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 back
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
									
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 left
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
								
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 right
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
									
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 top
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
									
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 bottom
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z
	};

	//Add temp Colors to Vector
	for (size_t i = 0; i < 72; i++)
	{
		colors.push_back(tempColors[i]);
	}

	//Check if cube is mapped, if yes UV array is different
	if (isCubeMapped)
	{
		ReadFile("./Data/Objects/Cube/CubeMapUVs.txt", UVS);
	}
	else
	{
		//Read UVs for cube
		ReadFile("./Data/Objects/Cube/CubeSingleTextureUVs.txt", UVS);
	}

	//Load Texture
	texture1.Load(filepath, textureID);
}

//-------------------------------------------------------------------------------
//Constructor Double Texture / not affected by light
//------------------------------------------------------------------------------
Cube::Cube(std::vector<std::string>& vector, std::string textureID)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//Set color was white
	glm::vec3 temp_rgb = glm::vec3(1.0f);
	//Set cube to single textured
	isTextured = 1;
	isDoubleTextured = 0;

	//Set Cube to is Mapped
	isCubeMapped = true;

	//Load Cube Map Texture

	skyBoxTexture.LoadCubeMap(vector, textureID);
}

//-------------------------------------------------------------------------------
//Constructor Double Texture / not affected by light
//-------------------------------------------------------------------------------
Cube::Cube(std::string filepath, std::string filepath2, std::string textureID, std::string textureID2)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//Set color was white
	glm::vec3 temp_rgb = glm::vec3(1.0f);

	//Set cube Double Textured
	isTextured = 1;
	isDoubleTextured = 1;

	//Set Cube to not mapped (This variable is only on for the proper cube Mapping)
	isCubeMapped = false;

	//Temp Color array for cube colors
	GLfloat tempColors[]{ temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face1 front
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
			
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 back
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
			
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 left
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
			
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 right
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
			
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 top
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
				
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 bottom
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z
	};

	//Add temp Colors to Vector
	for (size_t i = 0; i < 72; i++)
	{
		colors.push_back(tempColors[i]);
	}

	//Read UVs for cube
	ReadFile("./Data/Objects/Cube/CubeSingleTextureUVs.txt", UVS);

	//Load Textures
	texture1.Load(filepath, textureID);
	texture2.Load(filepath2, textureID2);
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Cube::~Cube()
{
	Destroy();
}

//-------------------------------------------------------------------------------
//Default initializing function for all cuber constructors
//-------------------------------------------------------------------------------
void Cube::Create(std::string shaderRef)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	collider.SetDimension(1.0f, 1.0f, 1.0f);

	//Set EBO/VAO and VBOs to default
	EBO = 0;
	VAO = 0;
	VBO_color = 0;
	VBO_vertex = 0;
	VBO_normal = 0;

	//Set Position
	position = glm::vec3(1.0f);

	//Set Shininess
	material->SetShine(1.0f);

	//Set programString to pass string
	shader = shaderRef; 

	isHighlighted = 1;

	//--------------------------------------------
	//Get Attributes
	//--------------------------------------------

	//Get Attributes from Light Shaders
	if (shader == "Lighting")
	{
		isLit = 1;

		ID_vertex = TheShader::Instance()->GetAttributeID("Lighting_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("Lighting_normalIn");

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

		isLit = 0;

		ID_color = TheShader::Instance()->GetAttributeID("Lightless_colorIn");
		ID_vertex = TheShader::Instance()->GetAttributeID("Lightless_vertexIn");

		if (isTextured == 1)
		{
			ID_texture = TheShader::Instance()->GetAttributeID("Lightless_textureIn");
		}
	}
	//Get Attributes from LightMap Shaders
	else if (shader == "LightMap")
	{
		isLit = 1;

		ID_vertex = TheShader::Instance()->GetAttributeID("LightMap_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("LightMap_normalIn");
		ID_texture = TheShader::Instance()->GetAttributeID("LightMap_textureIn");
		
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
	}
	else if (shader == "Cubemap")
	{
		isLit = 1;

		ID_vertex = TheShader::Instance()->GetAttributeID("Cubemap_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("Cubemap_normalIn");
	}
	else if (shader == "Skybox")
	{
		isLit = 1;

		ID_vertex = TheShader::Instance()->GetAttributeID("Skybox_vertexIn");
	}
	else
	{
		TheDebug::Log("Cube is being Created with an unavailable shader, that needs to be overloaded", ALERT);
	}

	//--------------------------------------------
	//Read Files
	//--------------------------------------------

	//Read vertices for cube
	ReadFile("./Data/Objects/Cube/CubeVertices.txt", VERTICES);

	//Read vertices for cube
	ReadFile("./Data/Objects/Cube/CubeIndices.txt", INDICES);

	//Read normals for cube
	ReadFile("./Data/Objects/Cube/CubeNormals.txt", NORMALS);

	CalculateTangents();
	//Bind and get arrays

	buffer->GenerateVertexArrays(1, &VAO);
	buffer->BindVertexArrays(VAO);

	//Fill and link Vertex VBO
	buffer->GenerateBuffers(1, &VBO_vertex);
	buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
	buffer->FillBuffer(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_vertex);

	if (isLit || shader == "Cubemap")
	{
		if (shader != "Skybox") 	
		{
			//Fill and link normal VBO
			buffer->GenerateBuffers(1, &VBO_normal);
			buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_normal);
			buffer->FillBuffer(GL_ARRAY_BUFFER, normals, GL_STATIC_DRAW);
			buffer->LinkToShader(ID_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);
			buffer->EnableVertexArray(ID_normal);
		}
	}
	else
	{
		if (shader != "Skybox" && shader !=  "Cubemap")
		{
			//Fill and link Color VBO
			buffer->GenerateBuffers(1, &VBO_color);
			buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_color);
			buffer->FillBuffer(GL_ARRAY_BUFFER, colors, GL_STATIC_DRAW);
			buffer->LinkToShader(ID_color, 3, GL_FLOAT, GL_FALSE, 0, 0);
			buffer->EnableVertexArray(ID_color);
		}
	}

	//Check if cube is textured
	if (isTextured == 1 && shader != "Cubemap" && shader != "Skybox")
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
	}
	//----------------------------- 
	//EBO
	//----------------------------- 

	//Generate Buffer
	buffer->GenerateBuffers(1, &EBO);
	buffer->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	buffer->FillBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW);
	buffer->BindVertexArrays(0);
	
	//----------------------------- 
	//Send texture information
	//-----------------------------

	if (isLit == 1 && shader != "LightMap" && shader !=  "Toon")
	{
		TheShader::Instance()->SendUniformData("Lighting_isTextured", isTextured);

		TheShader::Instance()->SendUniformData("Lighting_isDoubleTextured", isDoubleTextured);
	}
	else if(isLit == 0)
	{
		TheShader::Instance()->SendUniformData("Lightless_isTextured", isTextured);
	}

	TheShader::Instance()->SendUniformData("Lighting_textureImage1", 0);
	TheShader::Instance()->SendUniformData("Lighting_textureImage2", 1);

	TheShader::Instance()->SendUniformData("ShadowMapping_diffuseTexture", 0);
	TheShader::Instance()->SendUniformData("ShadowMapping_shadowMap", 1);

	TheShader::Instance()->SendUniformData("Skybox_skybox", 0);
	TheShader::Instance()->SendUniformData("Cubemap_skybox", 0);
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void Cube::Update()
{
	UpdateCollider();
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void Cube::Draw()
{
	//----------------------------------------------
	//Send Cube's material data to shader
	//---------------------------------------------
	if (shader != "Skybox")
	{
		SendModelInformation(shader);
	}

	if (shader != "ShadowMapGen" &&  shader != "ShadowMapping" && shader != "NormalMapping" && shader != "Skybox" && shader != "Cubemap")
	{
		//Check if Cube is affected by light
		if (isLit == 1)
		{
			//Send material shininess information
			SendShineData();

			if (shader != "LightMap")
			{
				//Send material ambient information
				SendAmbientData();

				//Send material specular information
				SendSpecularData();

				//Send material diffuse information
				SendDiffuseData();
			}
		}
	}

	//Use Shader
	TheShader::Instance()->UseShader(shader.c_str());

	if (shader == "Skybox")
	{
		glDepthFunc(GL_LEQUAL);
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
	//Check if it is textured

	if (shader != "ShadowMapGen")
	{
		if (isTextured == 1)
		{
			//Make first texture active
			glActiveTexture(GL_TEXTURE0);

			//Bind Texture
			if (shader == "Skybox" || shader == "Cubemap")
			{
				skyBoxTexture.Bind();
			}
			else
			{
				texture1.Bind();
			}

			//Check if it is double textured
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
		}
	}

	//Bind Vertex Array And draw cube
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//Change depth function so depth test passes when values are equal to depth buffer's content
	if (shader == "Skybox")
	{
		glDepthFunc(GL_LESS);
	}
	
}

//-------------------------------------------------------------------------------
//Destroy
//-------------------------------------------------------------------------------
void Cube::Destroy()
{
	//Delete VBOS
	glDeleteBuffers(1, &VBO_vertex);
	glDeleteBuffers(1, &VBO_color);
	glDeleteBuffers(1, &VBO_texture);

	//Delete EBOS
	glDeleteBuffers(1, &EBO);

	//Delete VAOs
	glDeleteVertexArrays(1, &VAO);

	//Delete IDS
	glDisableVertexAttribArray(ID_vertex);
	glDisableVertexAttribArray(ID_color);
	glDisableVertexAttribArray(ID_texture);
	glDisableVertexAttribArray(ID_normal);
}
