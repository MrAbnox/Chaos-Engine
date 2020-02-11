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
		BindUniform("Lighting_model");
		BindUniform("Lighting_cameraPos");
		BindUniform("Lighting_projection");
		BindUniform("Lighting_isTextured");
		BindUniform("Lighting_isDoubleTextured");

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

		BindUniform("Lighting_pointLightsNumber");
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
	}
}

//-------------------------------------------------------------------------------
//Create the Screen manager statically (only happens once) and return it
//-------------------------------------------------------------------------------
bool TheShader::CreateProgram(const GLchar* name)
{
	bool isProgramInMap = false;

	//Create shader program
	m_shaderProgramID = glCreateProgram();

	//-----------------------------  Check if program was created properly

	if (m_shaderProgramID <= 0)
	{
		TheDebug::Log("Could not create Shader program", ALERT);

		return false;
	}

	//----------------------------- Check the map if the program has been added already

	for (auto const& str : m_programMap)
	{
		if (str.first == name)
		{
			std::string tempString = "The programID " + str.first + "is already in the map";
			isProgramInMap = true;
			TheDebug::Log(tempString, ALERT);

			return false;
		}
	}

	//----------------------------- Check if the id from the shader is not in the map, add it to the map

	if (isProgramInMap == false)
	{
		m_programMap[name] = m_shaderProgramID;
	}

	return true;
}


//-------------------------------------------------------------------------------
//Create the shaders and check if they were properly created
//-------------------------------------------------------------------------------
bool TheShader::CreateShader(Shaders s, const GLchar* name)
{
	GLint m_shaderID = -1;
	bool isShaderInMap = false;

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

		//----------------------------- Check the map if the vertex attribute has been added already

		for (auto const& str : m_fragShaderMap)
		{
			if (str.first == name)
			{
				std::string tempString = "The fragment shader: " + str.first +" is already in the frag Map";
				isShaderInMap = true;
				TheDebug::Log(tempString, ALERT); 

				return false;
			}
		}

		//----------------------------- Check if the id from the shader is not in the map, add it to the map

		if (isShaderInMap == false)
		{
			m_fragShaderMap[name] = m_shaderID;
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

		for (auto const& str : m_vertShaderMap)
		{
			if (str.first == name)
			{
				std::string tempString = "The vertex shader: " + str.first + " is already in the vert Map";
				isShaderInMap = true;
				TheDebug::Log(tempString, ALERT);

				return false;
			}
		}

		//----------------------------- Check if the id from the shader is not in the map, add it to the map

		if (isShaderInMap == false)
		{
			m_vertShaderMap[name] = m_shaderID;
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

	bool isShaderInMap = false;

	//------------------------------ Check what type of shader is getting compiled

	switch (s)
	{
	case FRAGMENT:

		//----------------------------- Check if the id from the shader is in the map, if yes set the shaderID to its ID

		for (auto const& str : m_fragShaderMap)
		{
			if (str.first == name)
			{
				isShaderInMap = true;

				shader_ID = str.second;
			}
		}

		//----------------------------- Check if shader is in the map

		if (isShaderInMap == false)
		{
			std::string tempS = "Shader " + (std::string)name + " needs to be created before being compiled";
			TheDebug::Log(tempS, ALERT);

			return false;
		}

		break;

	case VERTEX:

		//----------------------------- Check if the id from the shader is in the map, if yes set the shaderID to its ID

		for (auto const& str : m_vertShaderMap)
		{
			if (str.first == name)
			{
				isShaderInMap = true;

				shader_ID = str.second;
			}
		}

		//----------------------------- Check if shader is in the map

		if (isShaderInMap == false)
		{
			std::string tempS = "Shader " + (std::string)name + " needs to be created before being compiled";
			TheDebug::Log(tempS, ALERT);

			return false;
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
	bool isShaderInMap = false;

	GLint tempVertShaderID = -1;
	GLint tempFragShaderID = -1;

	//------------------------------ Check if shader is in the map

	for (auto const& str : m_vertShaderMap)
	{
		if (str.first == name)
		{
			isShaderInMap = true;

			tempVertShaderID = str.second;
		}
	}

	//------------------------------ Debug log if shader is not in map

	if (isShaderInMap == false)
	{
		std::string tempS = "Shader " + (std::string)name + " needs to be created before being compiled";
		TheDebug::Log(tempS, ALERT);

	}

	//------------------------------ Check if shader is in the map

	for (auto const& str : m_fragShaderMap)
	{
		if (str.first == name)
		{
			isShaderInMap = true;

			tempFragShaderID = str.second;
		}
	}

	//------------------------------ Debug log if shader is not in map

	if (isShaderInMap == false)
	{
		std::string tempS = "Shader " + (std::string)name + " needs to be created before being compiled";
		TheDebug::Log(tempS, ALERT);
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
	std::map<std::string, std::string> tempFragMap;

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
	ParseText(tempFRFileName, token, tempFragMap );

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

	//----------------------------- Check the map if programID is there

	for (auto const& str : m_programMap)
	{
		if (str.first == name)
		{
			tempID = str.second;
		}
	}

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
	bool isAttributeInMap = false;


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

		for (auto const& str : m_attributeMap)
		{
			if (str.first == attribute)
			{
				//----------------------------- Check the map if the vertex attribute has been added already

				std::string tempString = "The attribute: " + str.first + " is already in the attribute Map";
				isAttributeInMap = true;
				TheDebug::Log(tempString, ALERT);
			}
		}

		//----------------------------- Check which attribute map to add the attribute to
		//----------------------------- If the id from the shader is not in the map, add it to the map

		if (isAttributeInMap == false)
		{
			m_attributeMap[attribute] = tempID;
		}
	}
}


//-------------------------------------------------------------------------------
//Bind uniform functions
//-------------------------------------------------------------------------------
void TheShader::BindUniform(std::string uniform)
{
	//----------------------------- Parse 

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
		//----------------------------- Loop through map

		for (auto const& str : m_uniformMap)
		{
			//----------------------------- Check the map if the vertex Uniform has been added already

			if (str.first == uniform)
			{
				std::string tempString = "The uniform is already in the uniform Map";

				TheDebug::Log(tempString, ALERT);

				isUniformInMap = true;
			}
		}

		//----------------------------- Check which uniform map to add the attribute to
		//----------------------------- If the id from the shader is not in the map, add it to the map

		if (isUniformInMap == false)
		{
			m_uniformMap[uniform] = tempID;
		}

	}
}


//-------------------------------------------------------------------------------
//Get Uniform ID
//-------------------------------------------------------------------------------
GLuint TheShader::GetUniformID(const GLchar* uniform)
{
	//----------------------------- Declare temp variables

	bool isUniformInMap = false;
	GLint tempID = -1;

	//----------------------------- Loop through map

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			tempID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- Check map for Uniform, if found return ID, if not return -1


	if (isUniformInMap == true)
	{
		return tempID;
	}
	else
	{
		std::string tempS = (std::string)uniform + " can not be found";
		TheDebug::Log(tempS, ALERT);
		return -1;
	}
}


//-------------------------------------------------------------------------------
//Get Attribute ID
//-------------------------------------------------------------------------------
GLuint TheShader::GetAttributeID(const GLchar* attribute)
{

	//----------------------------- Declare temp variables

	bool isAttributeInMap = false;
	GLint tempID;

	//----------------------------- Loop through map

	for (auto const& str : m_attributeMap)
	{
		if (str.first == attribute)
		{
			tempID = str.second;
			isAttributeInMap = true;
		}
	}

	//----------------------------- Check map for Attribute, if found return ID, if not return -1

	if (isAttributeInMap == true)
	{
		return tempID;
	}
	else
	{
		std::string tempS = (std::string)attribute + " can not be found";
		TheDebug::Log(tempS, ALERT);
		return -1;
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}
	
	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform1i(uniformID, x);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform2i(uniformID, x, y);
	}
	else
	{ 
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{

		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform3i(uniformID, x, y, z);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{

		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform4i(uniformID, x, y, z, w);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform1ui(uniformID, x);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if(isUniformInMap == true)
	{
		glUniform2ui(uniformID, x, y);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform3ui(uniformID, x, y, z);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform4ui(uniformID, x, y, z, w);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform1f(uniformID, x);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform1f(uniformID, x);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform2f(uniformID, x, y);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform3f(uniformID, x, y, z);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform4f(uniformID, x, y, z, w);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform3f(uniformID, v3.x, v3.y, v3.z);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
}

void TheShader::SendUniformData(const std::string uniform, const glm::vec3& v3)
{
	
	//--------------------------------------------
	//Define Variables
	//--------------------------------------------

	//============================================

	GLint uniformID;

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform3f(uniformID, v3.x, v3.y, v3.z);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniform3fv(uniformID,count, value);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	if (isUniformInMap == true)
	{
		glUniformMatrix2fv(uniformID, count, boolean, &matrix[0][0]);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
		glUniformMatrix3fv(uniformID, count, boolean, &matrix[0][0]);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
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

	bool isUniformInMap = false;

	std::string tempString = uniform;
	std::vector<std::string> tempVector;

	//============================================

	//parse text
	ParseText(tempString, m_token, tempVector);

	//Use shader from parsed uniform text
	UseShader(tempVector[0].c_str());

	//----------------------------- Loop uniform map and check if the needed one is there

	for (auto const& str : m_uniformMap)
	{
		if (str.first == uniform)
		{
			uniformID = str.second;
			isUniformInMap = true;
		}
	}

	//----------------------------- If Uniform is found send data else send DebugLog

	if (isUniformInMap == true)
	{
 		glUniformMatrix4fv(uniformID, count, boolean, &matrix[0][0]);
	}
	else
	{
		std::string a = uniform;
		std::string tempString = "Uniform  '" + a + "' is not in map";
		TheDebug::Log(tempString, ALERT);
	}
}

