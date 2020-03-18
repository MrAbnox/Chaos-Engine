#include "TheShader.h"
#include "TheDebug.h"
#include "Tools.h"

#include <map>
#include <iostream>

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
TheShader::TheShader()
{
	isInitialized = false;
	m_token = '_';
}

//-------------------------------------------------------------------------------
//Create the Shader manager statically (only happens once) and return it
//-------------------------------------------------------------------------------
TheShader* TheShader::Instance()
{
	static TheShader* shaderManager = new TheShader;

	return shaderManager;
}

//-------------------------------------------------------------------------------
//Initialize Attributes and uniforms
//-------------------------------------------------------------------------------
void TheShader::Initialize()
{
	//check if it is initialized
	if (isInitialized == false)
	{
		//============================================
		//LIGHTING
		//============================================

		//----------------------------- Bind uniform variables

		BindUniform("Lighting_view");
		BindUniform("Lighting_shadowMap");
		BindUniform("Lighting_textureImage1");
		BindUniform("Lighting_textureImage2");
		BindUniform("Lighting_model");
		BindUniform("Lighting_cameraPos");
		BindUniform("Lighting_projection");
		BindUniform("Lighting_lightSpaceMatrix");
		BindUniform("Lighting_isTextured");
		BindUniform("Lighting_isDoubleTextured");
		BindUniform("Lighting_lightPos");

		BindUniform("Lighting_material.ambient");
		BindUniform("Lighting_material.diffuse");
		BindUniform("Lighting_material.specular");
		BindUniform("Lighting_material.shininess");

		BindUniform("Lighting_dirLight.direction");
		BindUniform("Lighting_dirLight.ambient");
		BindUniform("Lighting_dirLight.diffuse");
		BindUniform("Lighting_dirLight.specular");

		BindUniform("Lighting_spotLight.position");
		BindUniform("Lighting_spotLight.direction");
		BindUniform("Lighting_spotLight.ambient");
		BindUniform("Lighting_spotLight.diffuse");
		BindUniform("Lighting_spotLight.specular");
		BindUniform("Lighting_spotLight.linear");
		BindUniform("Lighting_spotLight.quadratic");
		BindUniform("Lighting_spotLight.constant");
		BindUniform("Lighting_spotLight.cutOff");
		BindUniform("Lighting_spotLight.outerCutOff");

		BindUniform("Lighting_pointLights[0].position");
		BindUniform("Lighting_pointLights[0].constant");
		BindUniform("Lighting_pointLights[0].linear");
		BindUniform("Lighting_pointLights[0].quadratic");
		BindUniform("Lighting_pointLights[0].ambient");
		BindUniform("Lighting_pointLights[0].diffuse");
		BindUniform("Lighting_pointLights[0].specular");
	
		BindUniform("Lighting_pointLights[1].position");
		BindUniform("Lighting_pointLights[1].constant");
		BindUniform("Lighting_pointLights[1].linear");
		BindUniform("Lighting_pointLights[1].quadratic");
		BindUniform("Lighting_pointLights[1].ambient");
		BindUniform("Lighting_pointLights[1].diffuse");
		BindUniform("Lighting_pointLights[1].specular");

		BindUniform("Lighting_pointLights[2].position");
		BindUniform("Lighting_pointLights[2].constant");
		BindUniform("Lighting_pointLights[2].linear");
		BindUniform("Lighting_pointLights[2].quadratic");
		BindUniform("Lighting_pointLights[2].ambient");
		BindUniform("Lighting_pointLights[2].diffuse");
		BindUniform("Lighting_pointLights[2].specular");

		BindUniform("Lighting_pointLights[3].position");
		BindUniform("Lighting_pointLights[3].constant");
		BindUniform("Lighting_pointLights[3].linear");
		BindUniform("Lighting_pointLights[3].quadratic");
		BindUniform("Lighting_pointLights[3].ambient");
		BindUniform("Lighting_pointLights[3].diffuse");
		BindUniform("Lighting_pointLights[3].specular");

		BindUniform("Lighting_numberPointLights");
		BindUniform("Lighting_numberSpotLights");
		BindUniform("Lighting_isDirectionalLight");


		//----------------------------- Bind Attribute variables

		BindAttribute("Lighting_normalIn");
		BindAttribute("Lighting_vertexIn");
		BindAttribute("Lighting_textureIn");


		//============================================
		//LightMap
		//============================================


		BindUniform("LightMap_view");
		BindUniform("LightMap_model");
		BindUniform("LightMap_cameraPos");
		BindUniform("LightMap_projection");
				
		BindUniform("LightMap_material.shininess");
		BindUniform("LightMap_diffuse");
		BindUniform("LightMap_specular");
				
		BindUniform("LightMap_light.ambient");
		BindUniform("LightMap_light.diffuse");
		BindUniform("LightMap_light.specular");
		BindUniform("LightMap_light.position");

		BindAttribute("LightMap_normalIn");
		BindAttribute("LightMap_vertexIn");
		BindAttribute("LightMap_textureIn");

		//============================================
		//LAMP
		//============================================

		//----------------------------- Bind uniform variables

		BindUniform("Lightless_view");
		BindUniform("Lightless_model");
		BindUniform("Lightless_projection");
		BindUniform("Lightless_isTextured");

		//----------------------------- Bind Attribute variables

		BindAttribute("Lightless_colorIn");
		BindAttribute("Lightless_vertexIn");
		BindAttribute("Lightless_textureIn");

		//Set shaders to initialized
		isInitialized = true;	

		//============================================
		//CARTOON SHADER
		//============================================

		//----------------------------- Bind uniform variables

		BindUniform("Toon_view");
		BindUniform("Toon_model");
		BindUniform("Toon_material.diffuse");
		BindUniform("Toon_material.ambient");
		BindUniform("Toon_material.color");
		BindUniform("Toon_projection");
		BindUniform("Toon_light.position");
		BindUniform("Toon_light.intensity");
		BindUniform("Toon_toon");
		BindUniform("Toon_position");
		BindUniform("Toon_cameraPos");

		//----------------------------- Bind Attribute variables

		BindAttribute("Toon_vertexIn");
		BindAttribute("Toon_normalIn");
		BindAttribute("Toon_textureIn");

		//============================================
		//Shadow Map Gen
		//============================================
		
		BindUniform("ShadowMapGen_model"); 
		BindUniform("ShadowMapGen_lightSpaceMatrix");

		//----------------------------- Bind Attribute variables

		BindAttribute("ShadowMapGen_vertexIn");


		//============================================
		//Shadow Mapping	
		//============================================

		BindUniform("ShadowMapping_view");
		BindUniform("ShadowMapping_model");
		BindUniform("ShadowMapping_projection");
		BindUniform("ShadowMapping_lightPos");
		BindUniform("ShadowMapping_viewPos");
		BindUniform("ShadowMapping_shadowMap");
		BindUniform("ShadowMapping_diffuseTexture"); 
		BindUniform("ShadowMapping_lightSpaceMatrix"); 

		//----------------------------- Bind Attribute variables

		BindAttribute("ShadowMapping_vertexIn");
		BindAttribute("ShadowMapping_normalIn");
		BindAttribute("ShadowMapping_textureIn");

		//============================================
		//Normal Mapping	
		//============================================

		BindUniform("NormalMapping_view");
		BindUniform("NormalMapping_model");
		BindUniform("NormalMapping_projection");
		BindUniform("NormalMapping_lightPos");
		BindUniform("NormalMapping_viewPos");
		BindUniform("NormalMapping_diffuseMap");
		BindUniform("NormalMapping_normalMap");
		BindUniform("NormalMapping_heightMap");
		BindUniform("NormalMapping_heightScale");

		//----------------------------- Bind Attribute variables

		BindAttribute("NormalMapping_vertexIn");
		BindAttribute("NormalMapping_normalIn");
		BindAttribute("NormalMapping_textureIn");
		BindAttribute("NormalMapping_tangentIn");
		BindAttribute("NormalMapping_bitangentIn");
	}
}

//-------------------------------------------------------------------------------
//Create the Screen manager statically (only happens once) and return it
//-------------------------------------------------------------------------------
bool TheShader::CreateProgram(const GLchar* name)
{
	std::map<std::string, GLint>::iterator it;

	//Create shader program
	m_shaderProgramID = glCreateProgram();

	//-----------------------------  Check if program was created properly

	if (m_shaderProgramID <= 0)
	{
		TheDebug::Log("Could not create Shader program", ALERT);

		return false;
	}

	//----------------------------- Check the map if the program has been added already

	it = m_programMap.find(name);

	//----------------------------- Check if the id from the shader is not in the map, add it to the map

	std::string temp = name;

	if (it == m_programMap.end())
	{
		m_programMap[name] = m_shaderProgramID;

		return true;
	}
	else
	{
		std::string tempString = "The programID " + temp + "is already in the map";
		TheDebug::Log(tempString, ALERT);
		return false;
	}

	return true;
}


//-------------------------------------------------------------------------------
//Create the shaders and check if they were properly created
//-------------------------------------------------------------------------------
bool TheShader::CreateShader(Shaders s, const GLchar* name)
{
	GLint m_shaderID = -1;
	std::map<std::string, GLint>::iterator it;
	std::string temp = name;
	//----------------------------- Check what type of shader is getting created

	switch (s)
	{
	case FRAGMENT:

		//Create a fragment shader
		m_shaderID = glCreateShader(GL_FRAGMENT_SHADER);

		//----------------------------- Check if fragment shader was properly created

		if (m_shaderID == -1)
		{
			TheDebug::Log("Fragment shader could no be created", ALERT);

			return false;
		}

		//----------------------------- Check the map if the frag attribute has been added already

		it = m_fragShaderMap.find(name);

		//----------------------------- Check if the id from the shader is not in the map, add it to the map

		if (it == m_fragShaderMap.end())
		{
			m_fragShaderMap[name] = m_shaderID;
			return true;
		}
		else
		{
			std::string tempString = "The programID " + temp + "is already in the map";
			TheDebug::Log(tempString, ALERT);
			return false;
		}

		break;

	case VERTEX:

		//Create a vertex shader
		m_shaderID = glCreateShader(GL_VERTEX_SHADER);

		//----------------------------- Check if vertex shader was properly created

		if (m_shaderID == -1)
		{
			TheDebug::Log("Vertex shader could not be created", ALERT);

			return false;
		}

		//----------------------------- Check the map if the vertex attribute has been added already

		it = m_vertShaderMap.find(name);

		//----------------------------- Check if the id from the shader is not in the map, add it to the map

		if (it == m_vertShaderMap.end())
		{
			m_vertShaderMap[name] = m_shaderID;
			return true;
		}
		else
		{
			std::string tempString = "The programID " + temp + "is already in the map";
			TheDebug::Log(tempString, ALERT);
			return false;
		}

		break;

	default:

		break;
	}

	return true;
}


//-------------------------------------------------------------------------------
//Check Shader file and parse it
//-------------------------------------------------------------------------------
bool TheShader::ParseShader(const std::string& filepath)
{
	//----------------------------- Declare variables and open shader file

	std::fstream file;
	std::string lineText = "";
	std::string finalString = "";

	file.open(filepath);

	//----------------------------- Check if the file was properly created

	if (!file)
	{
		//Could not find shader file
		TheDebug::Log("Could not find shader file!", ALERT);

		return false;
	}

	//----------------------------- Check file until the end
	while (!file.eof())
	{

		//----------------------------- Get each line add it to a string and separate it with a terminating null "\n" so OpenGL can distinguish each line seperately

		getline(file, lineText);
		finalString += lineText + "\n";

	}

	//Close file
	file.close();

	//Store string
	source = finalString;

	return true;
}


//-------------------------------------------------------------------------------
//Compile shader 
//-------------------------------------------------------------------------------
GLuint TheShader::CompileShader(const GLchar* name, Shaders s)
{
	//----------------------------- GLSL code converted to GLchar so OpenGL can read it


	const GLchar* finalCode = (const  GLchar*)(source.c_str());
	GLint compileResult;

	GLint shader_ID = -1;

	std::string temp = name;
	std::map<std::string, GLint>::iterator it;

	//------------------------------ Check what type of shader is getting compiled

	switch (s)
	{
	case FRAGMENT:

		//----------------------------- Check if the id from the shader is in the map, if yes set the shaderID to its ID

		it = m_fragShaderMap.find(name);

		//----------------------------- Check if shader is in the map

		if (it == m_fragShaderMap.end())
		{
			std::string tempS = "Shader " + (std::string)name + " needs to be created before being compiled";
			TheDebug::Log(tempS, ALERT);

			return false;
		}
		else
		{
			shader_ID = it->second;
		}

		break;

	case VERTEX:

		//----------------------------- Check if the id from the shader is in the map, if yes set the shaderID to its ID

		it = m_vertShaderMap.find(name);

		//----------------------------- Check if shader is in the map

		if (it == m_vertShaderMap.end())
		{
			std::string tempS = "Shader " + (std::string)name + " needs to be created before being compiled";
			TheDebug::Log(tempS, ALERT);

			return false;
		}
		else
		{
			shader_ID = it->second;
		}

		break;

	default:

		break;

	}

	//----------------------------- Bound source code with shader object

	glShaderSource(shader_ID, 1, &finalCode, NULL);

	//----------------------------- Compile shader code

	glCompileShader(shader_ID);

	//----------------------------- Check if shader ID is valid

	if (shader_ID == -1)
	{
		std::string tempS = "Shader " + (std::string)name + " is invalid";
		TheDebug::Log(tempS, ALERT);
	}

	//----------------------------- Check compile status

	glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &compileResult);

	//----------------------------------------------------------
	//Check if Shader Compilation fails
	//----------------------------------------------------------

	//----------------------------- If compile status has failed 

	if (compileResult == GL_FALSE)
	{
		//----------------------------- Debug log the compile error

		GLchar error[1000];
		GLsizei length = 1000;

		glGetShaderInfoLog(shader_ID, 1000, &length, error);

		TheDebug::Log(error, ALERT);

		return false;
	}


	return true;
}


//-------------------------------------------------------------------------------
//Create the Screen manager statically (only happens once) and return it
//-------------------------------------------------------------------------------
void TheShader::AttachShader(const GLchar* name)
{
	std::string temp = name;
	std::map<std::string, GLint>::iterator it;
	std::map<std::string, GLint>::iterator it2;

	GLint tempVertShaderID = -1;
	GLint tempFragShaderID = -1;

	//------------------------------ Check if shader is in the map

	it = m_vertShaderMap.find(name);

	if (it == m_vertShaderMap.end())
	{
		std::string tempS = "Shader " + (std::string)name + " needs to be created before being compiled";
		TheDebug::Log(tempS, ALERT);
	}
	else
	{
		tempVertShaderID = it->second;
	}

	//------------------------------ Check if shader is in the map

	it2 = m_fragShaderMap.find(name);

	if(it2 == m_fragShaderMap.end())
	{
		std::string tempS = "Shader " + (std::string)name + " needs to be created before being compiled";
		TheDebug::Log(tempS, ALERT);
	}
	else
	{
		tempFragShaderID = it2->second;
	}

	//----------------------------- Attach shaders to program

	glAttachShader(m_shaderProgramID, tempVertShaderID);
	glAttachShader(m_shaderProgramID, tempFragShaderID);

}


//-------------------------------------------------------------------------------
//Create the Screen manager statically (only happens once) and return it
//-------------------------------------------------------------------------------
bool TheShader::LinkShader()
{	
	GLint linkResult = 0;

	//----------------------------- Link all inputs and outputs of the shader program

	glLinkProgram(m_shaderProgramID);

	//----------------------------- Link all inputs and outputs of the shader program

	glUseProgram(m_shaderProgramID);

	//----------------------------------------------------------
	//Check if Shader Compilation fails
	//----------------------------------------------------------

	//----------------------------- Check Link status

	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &linkResult);

	//----------------------------- If link status has failed

	if (linkResult == GL_FALSE)
	{
		//----------------------------- Debug log the link error

		GLchar error[1000];
		GLsizei length = 1000;

		glGetProgramInfoLog(m_shaderProgramID, 1000, &length, error);

		TheDebug::Log(error, ALERT);

		return false;
	}
	else
	{
		return true;
	}
}


//-------------------------------------------------------------------------------
//Detach shaders and delete them
//-------------------------------------------------------------------------------
void TheShader::DestroyShader()
{
	//----------------------------- Loop shader maps and detach shaders fropm program

	for (auto const& pr : m_programMap)
	{
		for (auto const& str : m_vertShaderMap)
		{
			glDetachShader(pr.second, str.second);
		}

		for (auto const& str : m_fragShaderMap)
		{
			glDetachShader(pr.second, str.second);
		}
	}

	//----------------------------- Loop shader maps and destroy shaders

	for (auto const& str : m_fragShaderMap)
	{
		glDeleteShader(str.second);
	}

	for (auto const& str : m_fragShaderMap)
	{
		glDeleteShader(str.second);
	}

	//----------------------------- Loop program map and destroy programs

	for (auto const& str : m_programMap)
	{
		glDeleteProgram(str.second);
	}
}

//-------------------------------------------------------------------------------
//Create a vertex shader and a fragment shader, compile them and attach & link them together
//-------------------------------------------------------------------------------
bool TheShader::CreateShaders(std::string VSfilepath, std::string FRfilepath)
{
	//----------------------------- Create temp shader maps
	
	std::map<std::string, std::string> tempVertexMap;

	//create temp token
	char token = '.';

	//----------------------------- Set temp variables to fileNames

	std::string tempVSFileName = VSfilepath;
	std::string tempFRFileName = FRfilepath;

	//----------------------------- Set temp variables to filepaths with folder name

	std::string tempVSFilePath = "./Shaders/" + VSfilepath;
	std::string tempFRFilePath = "./Shaders/" + FRfilepath; 

	//----------------------------- Parse file paths so the name before the dot becomes the shaders names

	ParseText(tempVSFileName, token, tempVertexMap );	

	//----------------------------- Create temp strings to store the shaders names before the dot: ex: was "main.frag" became "main"

	std::string tempName;

	//----------------------------- loop through map and store the string name into the temp variable

	for (auto const& str : tempVertexMap)
	{
		if (str.second == "vert")
		{
			tempName = str.first;
		}
	}

	//Create program with the first name 
	if (!CreateProgram(tempName.c_str()) == true) 
	{ 
		TheDebug::Log("Can't create program", ALERT); 
		return false;
	}

	//Create vertex shader with vername
	if (!CreateShader(VERTEX, tempName.c_str()) == true)
	{ 
		TheDebug::Log("Can't create shaders", ALERT); 
		return false;
	}

	//Create fragment shader with vername
	if (!CreateShader(FRAGMENT, tempName.c_str()) == true) 
	{
		TheDebug::Log("Can't create shaders", ALERT); 
		return false;
	}

	//Parse vertex shader
	if (!ParseShader(tempVSFilePath) == true)
	{
		TheDebug::Log("Can't Parse Vertex shader.", ALERT);
		return false;
	}

	//Compile vertex shader
	if (!CompileShader(tempName.c_str(), VERTEX) == true) 
	{
		TheDebug::Log("Can't Compile Vertex shader.", ALERT);
		return false;
	}

	//Parse fragment shader
	if (!ParseShader(tempFRFilePath) == true) {
		TheDebug::Log("Can't Parse Fragment shader.", ALERT); 
		return false;
	}

	//Compile fragment shader
	if (!CompileShader(tempName.c_str(), FRAGMENT) == true) 
	{
		TheDebug::Log("Can't Compile Vertex shader.", ALERT);
		return false;
	}

	//Attach both vertex and fragment shader together
	AttachShader(tempName.c_str());

	//Link shaders!
	if (!LinkShader() == true) {
		TheDebug::Log("Can't Link shaders.", ALERT); 
		return false;
	}

	return true;
}

bool TheShader::UseShader(const GLchar* name)
{
	GLint tempID = -1;
	std::map<std::string, GLint>::iterator it;

	//----------------------------- Check the map if programID is there

	it = m_programMap.find(name);

	tempID = it->second;

	//----------------------------- Check if programID is valid

	if (tempID < 0)
	{
		std::string tempString = "The programID " + (std::string)name + " can not be found";
		TheDebug::Log(tempString, ALERT);

		return false;
	}

	//Set Shader programID to one that is to be used
	m_shaderProgramID = tempID;

	//Use the programID
	glUseProgram(m_shaderProgramID);

	return true;
}


//-------------------------------------------------------------------------------
//Bind attribute function
//-------------------------------------------------------------------------------
void TheShader::BindAttribute( std::string attribute)
{

	std::map<std::string, GLint>::iterator it;

	//Parser code
	std::string tempString = attribute;
	std::vector<std::string> tempVector;

	ParseText(tempString, m_token, tempVector);

	UseShader(tempVector[0].c_str());

	//----------------------------- Get location of pre-determined Attribute location

	GLint tempID = glGetAttribLocation(m_shaderProgramID, tempVector[1].c_str());

	//----------------------------- Check if Attribute is valid

	if (tempID == -1)
	{
		std::string tempString = "The attribute ID " + attribute + " is invalid";

		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		//----------------------------- Loop through map

		it = m_attributeMap.find(attribute);

		if (it == m_attributeMap.end())
		{
			m_attributeMap[attribute] = tempID;
		}
		else
		{
			//----------------------------- Check the map if the vertex attribute has been added already

			std::string tempString = "The attribute: " + it->first + " is already in the attribute Map";
			TheDebug::Log(tempString, ALERT);
		}
	}
}


//-------------------------------------------------------------------------------
//Bind uniform functions
//-------------------------------------------------------------------------------
void TheShader::BindUniform(std::string uniform)
{
	//----------------------------- Parse 

	std::map<std::string, GLint>::iterator it;
	std::string tempString = uniform;
	std::vector<std::string> tempVector;
	ParseText(tempString, m_token, tempVector);

	UseShader(tempVector[0].c_str());

	//----------------------------- Get location of pre-determined Uniform location

	GLint tempID = glGetUniformLocation(m_shaderProgramID, tempVector[1].c_str());
	
	bool isUniformInMap = false;

	//----------------------------- Check if Uniform is valid

	if (tempID == -1)
	{
		std::string tempString = "The uniform ID " + uniform + " is invalid";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		it = m_uniformMap.find(uniform);

		if (it == m_uniformMap.end())
		{
			m_uniformMap[uniform] = tempID;
		}
		else
		{
			//----------------------------- Check the map if the vertex attribute has been added already

			std::string tempString = "The uniform is already in the uniform Map";
			TheDebug::Log(tempString, ALERT);
		}
	}
}


//-------------------------------------------------------------------------------
//Get Uniform ID
//-------------------------------------------------------------------------------
GLuint TheShader::GetUniformID(const GLchar* uniform)
{
	//----------------------------- Declare temp variables

	std::map<std::string, GLint>::iterator it;
	GLint tempID = -1;

	//----------------------------- Loop through map

	it = m_uniformMap.find(uniform);

	if (it == m_uniformMap.end())
	{
		std::string tempS = (std::string)uniform + " can not be found";
		TheDebug::Log(tempS, ALERT);
		return -1;
	}
	else
	{
		tempID = it->second;
		return tempID;
	}
}


//-------------------------------------------------------------------------------
//Get Attribute ID
//-------------------------------------------------------------------------------
GLuint TheShader::GetAttributeID(const GLchar* attribute)
{
	//----------------------------- Declare temp variables

	GLint tempID;
	std::map<std::string, GLint>::iterator it;

	//----------------------------- Loop through map
	it = m_attributeMap.find(attribute);

	if (it == m_attributeMap.end())
	{
		std::string tempS = (std::string)attribute + " can not be found";
		TheDebug::Log(tempS, ALERT);
		return -1;
	}
	else
	{
		tempID = it->second;
		return tempID;
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLint& x)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		BindUniform(uniform);
		it = m_uniformMap.find(uniform);
		uniformID = it->second;
	}
	else
	{
		glUniform1i(uniformID, x);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLint& x, const GLint& y)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform2i(uniformID, x, y);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLint& x, const GLint& y, const GLint& z)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform3i(uniformID, x, y, z);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLint& x, const GLint& y, const GLint& z, const GLint& w)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform4i(uniformID, x, y, z, w);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLuint& x)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform1ui(uniformID, x);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLuint& x, const GLuint& y)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform2ui(uniformID, x, y);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLuint& x, const GLuint& y, const GLuint& z)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform3ui(uniformID, x, y, z);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLuint& x, const GLuint& y, const GLuint& z, const GLuint& w)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform4ui(uniformID, x, y, z, w);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const std::string uniform, const GLfloat& x)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform1f(uniformID, x);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLfloat& x)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform1f(uniformID, x);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLfloat& x, const GLfloat& y)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform2f(uniformID, x, y);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLfloat& x, const GLfloat& y, const GLfloat& z)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform3f(uniformID, x, y, z);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLfloat& x, const GLfloat& y, const GLfloat& z, const GLfloat& w)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform4f(uniformID, x, y, z, w);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const glm::vec3& v3)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform3f(uniformID, v3.x, v3.y, v3.z);
	}
}

void TheShader::SendUniformData(const std::string uniform, const glm::vec3& v3)
{
	
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform3f(uniformID, v3.x, v3.y, v3.z);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, GLsizei count, const GLfloat* value)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniform3fv(uniformID, count, value);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLint& count, const bool& boolean, const glm::mat2& matrix)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniformMatrix2fv(uniformID, count, boolean, &matrix[0][0]);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLint& count, const bool& boolean, const glm::mat3& matrix)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniformMatrix3fv(uniformID, count, boolean, &matrix[0][0]);
	}
}

//-------------------------------------------------------------------------------
//Send Uniform Data
//-------------------------------------------------------------------------------
void TheShader::SendUniformData(const GLchar* uniform, const GLint& count, const bool& boolean, const glm::mat4& matrix)
{
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	std::map<std::string, GLint>::iterator it;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	it = m_uniformMap.find(uniform);
	uniformID = it->second;

	//----------------------------- If Uniform is found send data else send DebugLog

	if (it == m_uniformMap.end())
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
	else
	{
		glUniformMatrix4fv(uniformID, count, boolean, &matrix[0][0]);
	}
}

