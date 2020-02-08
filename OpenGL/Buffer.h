#ifndef THEBUFFER_H
#define THEBUFFER_H

#include "glad.h"

#include <glm.hpp>
#include <SDL.h>
#include <vector>
#include <string>
#include <map>
#include <gtc/matrix_transform.hpp>


class Buffer 
{
public:

	Buffer();
	~Buffer();

public:

	virtual void Update() {};
	virtual void Draw() {};

public:

	void GenerateBuffers(GLsizei n, GLuint* buffers);
	void GenerateVertexArrays(GLsizei n, GLuint* arrays);

public:

	void BindBuffer(GLenum target, GLuint& buffer);
	void BindVertexArrays(GLuint array);

public:

	void FillBuffer(GLenum target, std::vector<GLfloat> vector, GLenum usage);
	void FillBuffer(GLenum target, std::vector<GLint> vector, GLenum usage);
	void FillBuffer(GLenum target, GLint* array, GLenum& usage);
	void FillBuffer(GLenum target, GLintptr offset, const void* data, GLsizeiptr size);

public:

	void AppendData(GLenum target, std::vector<GLfloat> vector, GLenum usage);
	void AppendData(GLenum target, GLint* array, const void* data);
	void AppendData(GLenum target, GLsizeiptr& size, const void* data, GLenum& usage);

public:

	void LinkToShader(GLint id, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

public:

	void EnableVertexArray(GLint id);

public:

	void DeleteBuffer(GLsizei& n, const GLuint* buffers);
	void DeleteVertexArrays(GLsizei n, const GLuint* arrays);

private:

	static std::map<std::string, Buffer>* s_bufferMap;

};

#endif // !THEBUFFERMANAGER_H