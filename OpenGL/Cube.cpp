#include "Cube.h"
#include "TheShader.h"
#include "Tools.h"

//-------------------------------------------------------------------------------
//Constructor No texture
//-------------------------------------------------------------------------------
Cube::Cube(glm::vec3 rgb)
{	
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	//Set color v3
	v3_rgb = rgb;

	//Set cube to not textured at all
	m_isTextured = 0;
	isDoubleTextured = 0;

	//Set Cube to not mapped (This variable is only on for the proper cube Mapping)
	m_isCubeMapped = false;

	//============================================
	
	//----------------------------- Temp Color array for cube colors

	GLfloat tempColors[]{ rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face1 front
						  rgb.x, rgb.y, rgb.z,
								
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 back
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
									
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 left
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
								
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 right
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
								
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 top
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
									
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 bottom
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z
	};

	//----------------------------- Add temp Colors to Vector


	for (size_t i = 0; i < 72; i++)
	{
		m_colors.push_back(tempColors[i]);
	}
}

//-------------------------------------------------------------------------------
//Constructor One Texture / not affected by light
//-------------------------------------------------------------------------------
Cube::Cube(bool& isCubeMapped, glm::vec3 rgb, std::string filepath, std::string textureID)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	//Set color v3
	v3_rgb = rgb;

	//Set cube to single textured
	m_isTextured = 1;
	isDoubleTextured = 0;

	//Set Cube to not mapped (This variable is only on for the proper cube Mapping)
	m_isCubeMapped = false;

	//============================================

	//----------------------------- Temp Color array for cube colors

	GLfloat tempColors[]{ rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face1 front
						  rgb.x, rgb.y, rgb.z,
								
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 back
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
									
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 left
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
								
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 right
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
									
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 top
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
									
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 bottom
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z
	};

	//----------------------------- Add temp Colors to Vector

	for (size_t i = 0; i < 72; i++)
	{
		m_colors.push_back(tempColors[i]);
	}

	//----------------------------- Check if cube is mapped, if yes UV array is different

	if (isCubeMapped)
	{
		ReadFile("./Data/Objects/Cube/CubeMapUVs.txt", UVS);
	}
	else
	{
		//----------------------------- Read UVs for cube

		ReadFile("./Data/Objects/Cube/CubeSingleTextureUVs.txt", UVS);

	}

	//----------------------------- Load Texture
	
	m_texture1.Load(filepath, textureID);
}

//-------------------------------------------------------------------------------
//Constructor Double Texture / not affected by light
//------------------------------------------------------------------------------
Cube::Cube(glm::vec3 rgb, std::vector<std::string> vector, std::string textureID)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	//Set color v3
	v3_rgb = rgb;

	//Set cube to single textured
	m_isTextured = 1;
	isDoubleTextured = 0;

	//Set Cube to is Mapped
	m_isCubeMapped = true;

	//============================================

	//----------------------------- Temp Color array for cube colors

	GLfloat tempColors[]{ rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face1 front
						  rgb.x, rgb.y, rgb.z,

						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 back
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,

						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 left
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,

						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 right
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,

						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 top
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,

						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 bottom
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z
	};

	//----------------------------- Add temp Colors to Vector

	for (size_t i = 0; i < 72; i++)
	{
		m_colors.push_back(tempColors[i]);
	}

	//----------------------------- Load Cube Map Texture

	m_texture1.LoadCubeMap(vector, textureID);
}

//-------------------------------------------------------------------------------
//Constructor Double Texture / not affected by light
//-------------------------------------------------------------------------------
Cube::Cube(glm::vec3 rgb, std::string filepath, std::string filepath2, std::string textureID, std::string textureID2)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	//Set color vector
	v3_rgb = rgb;

	//Set cube Double Textured
	m_isTextured = 1;
	isDoubleTextured = 1;

	//Set Cube to not mapped (This variable is only on for the proper cube Mapping)
	m_isCubeMapped = false;

	//============================================

	//----------------------------- Temp Color array for cube colors

	GLfloat tempColors[]{ rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face1 front
						  rgb.x, rgb.y, rgb.z,
			
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 back
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
			
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 left
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
			
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 right
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
			
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 top
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,
				
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z,								//#face2 bottom
						  rgb.x, rgb.y, rgb.z,
						  rgb.x, rgb.y, rgb.z
	};

	//----------------------------- Add temp Colors to Vector

	for (size_t i = 0; i < 72; i++)
	{
		m_colors.push_back(tempColors[i]);
	}

	//Read UVs for cube
	ReadFile("./Data/Objects/Cube/CubeSingleTextureUVs.txt", UVS);

	//Load Textures
	m_texture1.Load(filepath, textureID);
	m_texture2.Load(filepath2, textureID2);
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
void Cube::Create(std::string shader)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	//Set EBO/VAO and VBOs to default
	m_EBO = 0;
	m_VAO = 0;
	VBO_color = 0;
	VBO_vertex = 0;
	VBO_normal = 0;

	//Set Position
	v3_position = glm::vec3(1.0f);

	//Set Shininess
	m_material.SetShine(1.0f);

	//Set Ambient
	m_material.SetAmbient(glm::vec3(1.0f));

	//Set Diffuse
	m_material.SetDiffuse(glm::vec3(1.0f));

	//Set Specular
	m_material.SetSpecular(glm::vec3(1.0f));

	//Set programString to pass string
	m_shader = shader; 

	//Set This Object to be able to send Coords to shader
	canSendCoords = true;

	m_isHighlighted = 1;

	//============================================

	//--------------------------------------------
	//Get Attributes
	//--------------------------------------------

	//Get Attributes from Light Shaders
	if (m_shader == "Lighting")
	{
		m_isLit = 1;

		ID_vertex = TheShader::Instance()->GetAttributeID("Lighting_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("Lighting_normalIn");

		if (m_isTextured == 1)
		{
			ID_texture = TheShader::Instance()->GetAttributeID("Lighting_textureIn");
		}
	}
	//Get Attributes from Lamp Shaders
	else if (m_shader == "Lightless")
	{

		m_isLit = 0;

		ID_color = TheShader::Instance()->GetAttributeID("Lightless_colorIn");
		ID_vertex = TheShader::Instance()->GetAttributeID("Lightless_vertexIn");

		if (m_isTextured == 1)
		{
			ID_texture = TheShader::Instance()->GetAttributeID("Lightless_textureIn");
		}
	}
	//Get Attributes from LightMap Shaders
	else if (m_shader == "LightMap")
	{
		m_isLit = 1;

		ID_vertex = TheShader::Instance()->GetAttributeID("LightMap_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("LightMap_normalIn");
		ID_texture = TheShader::Instance()->GetAttributeID("LightMap_textureIn");
		
	}
	else if (m_shader == "Toon")
	{

		m_isLit = 0;

		ID_vertex = TheShader::Instance()->GetAttributeID("Toon_vertexIn");
		ID_normal = TheShader::Instance()->GetAttributeID("Toon_normalIn");

		if (m_isTextured == 1)
		{
			ID_texture = TheShader::Instance()->GetAttributeID("Toon_textureIn");
		}
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


	//--------------------------------------------
	//BUFFERS 
	//--------------------------------------------

	//----------------------------- Bind and get arrays

	m_buffer.GenerateVertexArrays(1, &m_VAO);

	m_buffer.BindVertexArrays(m_VAO);

	//----------------------------- 
	//Vertices Buffer
	//----------------------------- 

	//Generate Buffer
	m_buffer.GenerateBuffers(1, &VBO_vertex);

	//Bind Buffer
	m_buffer.BindBuffer(GL_ARRAY_BUFFER, VBO_vertex);

	//Fill Buffer
	m_buffer.FillBuffer(GL_ARRAY_BUFFER, m_vertices, GL_STATIC_DRAW);

	//Link to shader
	m_buffer.LinkToShader(ID_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Enable Vertex Array
	m_buffer.EnableVertexArray(ID_vertex);

	//----------------------------- 
	//Normals Buffer
	//----------------------------- 

	//Check if cube is Lit
	if (m_isLit)
	{
		//Generate Buffer
		m_buffer.GenerateBuffers(1, &VBO_normal);

		//Bind Buffer
		m_buffer.BindBuffer(GL_ARRAY_BUFFER, VBO_normal);

		//Fill Buffer
		m_buffer.FillBuffer(GL_ARRAY_BUFFER, m_normals, GL_STATIC_DRAW);

		//Link to shader
		m_buffer.LinkToShader(ID_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Enable Vertex Array
		m_buffer.EnableVertexArray(ID_normal);
	}

	//----------------------------- 
	//Colors Buffer
	//----------------------------- 

	if (m_isLit == 0)
	{
		//Generate Buffer
		m_buffer.GenerateBuffers(1, &VBO_color);

		//Bind Buffer
		m_buffer.BindBuffer(GL_ARRAY_BUFFER, VBO_color);

		//Fill Buffer
		m_buffer.FillBuffer(GL_ARRAY_BUFFER, m_colors, GL_STATIC_DRAW);

		//Link to shader
		m_buffer.LinkToShader(ID_color, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Enable Vertex Array
		m_buffer.EnableVertexArray(ID_color);
	}

	//----------------------------- 
	//Textures Buffer
	//----------------------------- 

	//Check if cube is textured
	if (m_isTextured == 1)
	{

		//Generate Buffer
		m_buffer.GenerateBuffers(1, &VBO_texture);

		//Bind Buffer
		m_buffer.BindBuffer(GL_ARRAY_BUFFER, VBO_texture);

		//Fill Buffer
		m_buffer.FillBuffer(GL_ARRAY_BUFFER, m_UVs, GL_STATIC_DRAW);

		//Link to shader
		m_buffer.LinkToShader(ID_texture, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//Enable Vertex Array
		m_buffer.EnableVertexArray(ID_texture);
	}

	//----------------------------- 
	//EBO
	//----------------------------- 

	//Generate Buffer
	m_buffer.GenerateBuffers(1, &m_EBO);

	//Bind Buffer
	m_buffer.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	//Fill Buffer
	m_buffer.FillBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices, GL_STATIC_DRAW);

	//Bind Vertex Array
	m_buffer.BindVertexArrays(0);

	//----------------------------- 
	//Send texture information
	//-----------------------------

	if (m_isLit == 1 && m_shader != "LightMap" && m_shader !=  "Toon")
	{
		TheShader::Instance()->SendUniformData("Lighting_isTextured", m_isTextured);

		TheShader::Instance()->SendUniformData("Lighting_isDoubleTextured", isDoubleTextured);
	}
	else if(m_isLit == 0)
	{
		TheShader::Instance()->SendUniformData("Lightless_isTextured", m_isTextured);
	}
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void Cube::Update()
{

	//----------------------------------------------
	//Send Cube's material data to shader
	//---------------------------------------------

	//Check if Cube is affected by light
	if (m_isLit == 1)
	{
		//Send material shininess information
		SendShineData();

		if (m_shader != "LightMap")
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

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void Cube::Draw()
{
	//Use Shader
	TheShader::Instance()->UseShader(m_shader.c_str());

	if (m_isCubeMapped)
	{
		glDepthFunc(GL_LEQUAL);
	}

	//----------------------------- Check if it is textured

	if (m_isTextured == 1)
	{
		//Make first texture active
		glActiveTexture(GL_TEXTURE0);

		//Bind Texture
		m_texture1.Bind();

		//----------------------------- Check if it is double textured

		if (isDoubleTextured == 1)
		{
			//Make second texture active
			glActiveTexture(GL_TEXTURE1);

			//Bind Texture
			m_texture2.Bind();
		}
	}

	//----------------------------- Check if it is DoubleTextured, if yes send Uniform Texture information

	if (isDoubleTextured == 1)
	{
		if (m_shader == "Lighting")
		{
			TheShader::Instance()->SendUniformData("Lighting_textureImage1", 0);
			TheShader::Instance()->SendUniformData("Lighting_textureImage2", 1);
		}
		else if (m_shader == "LightMap")
		{
			TheShader::Instance()->SendUniformData("LightMap_diffuse", 0);
			TheShader::Instance()->SendUniformData("LightMap_specular", 1);
		}
	}

	if (m_shader == "Toon")
	{
		TheShader::Instance()->SendUniformData("Toon_material.color", v3_rgb);
		TheShader::Instance()->SendUniformData("Toon_toon", m_isHighlighted);
		TheShader::Instance()->SendUniformData("Toon_position", v3_position);
		TheShader::Instance()->SendUniformData("Toon_toon", v3_position);
		SendAmbientData();
		SendDiffuseData();
	}

	//----------------------------- Bind Vertex Array And draw cube

	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	//Change depth function so depth test passes when values are equal to depth buffer's content
	if (m_isCubeMapped)
	{
		glDepthFunc(GL_LESS);
	}
	
}

//-------------------------------------------------------------------------------
//Destroy
//-------------------------------------------------------------------------------
void Cube::Destroy()
{

	//----------------------------- Delete VBOS

	glDeleteBuffers(1, &VBO_vertex);
	glDeleteBuffers(1, &VBO_color);
	glDeleteBuffers(1, &VBO_texture);

	//----------------------------- Delete EBOS

	glDeleteBuffers(1, &m_EBO);

	//----------------------------- Delete VAOs

	glDeleteVertexArrays(1, &m_VAO);

	//----------------------------- Delete IDS

	glDisableVertexAttribArray(ID_vertex);
	glDisableVertexAttribArray(ID_color);
	glDisableVertexAttribArray(ID_texture);
	glDisableVertexAttribArray(ID_normal);
}
