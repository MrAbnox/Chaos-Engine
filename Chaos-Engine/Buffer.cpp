#include "Buffer.h"
#include "TheDebug.h"
#include <iostream>

std::map<std::string, Buffer>* Buffer::s_bufferMap = new std::map<std::string, Buffer>;

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Buffer::Buffer()
{
	name = "Buffer";
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Buffer::~Buffer()
{
	delete s_bufferMap;
}

//-------------------------------------------------------------------------------
//Generate Buffers
//-------------------------------------------------------------------------------
void Buffer::GenerateBuffers(GLsizei n, GLuint* buffers)
{
	glGenBuffers(n, buffers);

	if (buffers < 0)
	{
		TheDebug::Log("Buffer could not be generated", ALERT);
	}
}

//-------------------------------------------------------------------------------
//Generate Vertex Array(s)
//-------------------------------------------------------------------------------
void Buffer::GenerateVertexArrays(GLsizei n, GLuint* arrays)
{
	glGenVertexArrays(n, arrays);

	if (arrays < 0)
	{
		TheDebug::Log("Vertextex Arrays could not be generated", ALERT);
	}
}

//-------------------------------------------------------------------------------
//Bind Buffer
//-------------------------------------------------------------------------------
void Buffer::BindBuffer(GLenum target, GLuint& buffer)
{
	glBindBuffer(target, buffer);
}

//-------------------------------------------------------------------------------
//Bind Vertex Array(s)
//-------------------------------------------------------------------------------
void Buffer::BindVertexArrays(GLuint array)
{
	glBindVertexArray(array);

	if (array < 0)
	{
		TheDebug::Log("Vertextex Arrays could not be Bound", ALERT);
	}
}

//-------------------------------------------------------------------------------
//Fill Buffer functions
//-------------------------------------------------------------------------------
void Buffer::FillBuffer(GLenum target, std::vector<GLfloat> vector, GLenum usage)
{
	glBufferData(target, vector.size() * sizeof(GLfloat), &vector[0], usage);
}

void Buffer::FillBuffer(GLenum target, std::vector<GLint> vector, GLenum usage)
{
	glBufferData(target, vector.size() * sizeof(GLint), &vector[0], usage);
}

void Buffer::FillBuffer(GLenum target, GLint* vector, GLenum& usage)
{
	glBufferData(target, sizeof(vector), vector, usage);
}

void Buffer::FillBuffer(GLenum target, GLintptr offset, const void* data, GLsizeiptr size)
{
	glBufferData(target, offset, data, size);
}

//-------------------------------------------------------------------------------
//Append Data functions
//-------------------------------------------------------------------------------
void Buffer::AppendData(GLenum target, std::vector<GLfloat> vector, GLenum usage)
{
	glBufferSubData(target, vector.size() * sizeof(GLfloat), vector[0], &usage);
}

void Buffer::AppendData(GLenum target, GLint* array, const void* data)
{
	glBufferSubData(target, sizeof(array), *array, data);
}

void Buffer::AppendData(GLenum target, GLsizeiptr& size, const void* data, GLenum& usage)
{
	glBufferSubData(target, size, usage, data);
}

//-------------------------------------------------------------------------------
//Link vertex attribute to shader
//-------------------------------------------------------------------------------
void Buffer::LinkToShader(GLint id, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(id, size, type, normalized, stride, pointer);
}

void Buffer::EnableVertexArray(GLint id)
{
	glEnableVertexAttribArray(id);
}

//-------------------------------------------------------------------------------
//Delete Buffer
//-------------------------------------------------------------------------------
void Buffer::DeleteBuffer(GLsizei& n, const GLuint* buffers)
{
	glDeleteBuffers(n, buffers);
}

//-------------------------------------------------------------------------------
//Delete Vertex Array(s)
//-------------------------------------------------------------------------------
void Buffer::DeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
	glDeleteVertexArrays(n, arrays);
}
