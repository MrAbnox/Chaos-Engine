#ifndef THESHADER_H
#define THESHADER_H

#include <SDL.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "TheDebug.h"
#include "glad.h"
#include <glm.hpp>


enum Shaders
{
	FRAGMENT, VERTEX
};

typedef std::map<std::string, GLint> ShaderMap;

class TheShader
{
public:

	static TheShader* Instance();

public:
	
	void Initialize();

public:

	bool CreateProgram(const GLchar* name);
	bool CreateShader(Shaders s, const GLchar* name);

	bool ParseShader(const std::string& filepath);
	unsigned int CompileShader(const GLchar* name, Shaders s);

	void AttachShader(const GLchar* name);
	bool LinkShader();

	void DestroyShader();

	bool CreateShaders(std::string VSfilepath, std::string FRfilepath);

public:

	bool UseShader(const GLchar* name);

public:

	void BindAttribute(std::string attribute);
	void BindUniform(std::string uniform);

public:

	GLuint GetUniformID(const GLchar* uniform);
	GLuint GetAttributeID(const GLchar* attribute);

public:

	void SendUniformData(const GLchar* uniform, const GLint& x);
	void SendUniformData(const GLchar* uniform, const GLint& x,   const GLint& y);
	void SendUniformData(const GLchar* uniform, const GLint& x,   const GLint& y, const GLint& z);
	void SendUniformData(const GLchar* uniform, const GLint& x,   const GLint& y, const GLint& z, const GLint& w);
												 				 
	void SendUniformData(const GLchar* uniform, const GLuint& x);
	void SendUniformData(const GLchar* uniform, const GLuint& x,  const GLuint& y);
	void SendUniformData(const GLchar* uniform, const GLuint& x,  const GLuint& y, const GLuint& z);
	void SendUniformData(const GLchar* uniform, const GLuint& x,  const GLuint& y, const GLuint& z, const GLuint& w);

	void SendUniformData(const std::string uniform, const GLfloat& x);
																  
	void SendUniformData(const GLchar* uniform, const GLfloat& x);
	void SendUniformData(const GLchar* uniform, const GLfloat& x, const GLfloat& y);
	void SendUniformData(const GLchar* uniform, const GLfloat& x, const GLfloat& y, const GLfloat& z);
	void SendUniformData(const GLchar* uniform, const GLfloat& x, const GLfloat& y, const GLfloat& z, const GLfloat& w);

	void SendUniformData(const GLchar* uniform, const glm::vec3& v3);
	void SendUniformData(const std::string uniform, const glm::vec3& v3);

	void SendUniformData(const GLchar* uniform, GLsizei count, const GLfloat* value);
	
	void SendUniformData(const GLchar* uniform, const GLint& count, const bool& boolean, const glm::mat2& matrix);
	void SendUniformData(const GLchar* uniform, const GLint& count, const bool& boolean, const glm::mat3& matrix);
	void SendUniformData(const GLchar* uniform, const GLint& count, const bool& boolean, const glm::mat4& matrix);


private:

	TheShader();
	TheShader(const TheShader&);
	TheShader& operator=(const TheShader&);

private:

	bool isInitialized;

private:

	std::string source;

private:

	GLint m_shaderProgramID;

	GLchar m_token;

private:

	std::map<std::string, GLint> m_uniformMap;
	std::map<std::string, GLint> m_attributeMap;

	std::map<std::string, GLint> m_programMap;

	std::map<std::string, GLint> m_vertShaderMap;
	std::map<std::string, GLint> m_fragShaderMap;

};

#endif

