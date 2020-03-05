#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"
#include "Component.h"

#include <vector>
#include <string>
#include <map>
//do a typedef for texture map
/*typedef std::map<std::string, Texture>* TextureMap;*/

enum Filters
{
	NEAREST = GL_NEAREST,
	BILINEAR = GL_LINEAR,
	TRILINEAR = GL_LINEAR_MIPMAP_LINEAR,
	MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	MIPMAP_NEAREST_BILINEAR = GL_NEAREST_MIPMAP_LINEAR,
	MIPMAP_BILINEAR_NEAREST = GL_LINEAR_MIPMAP_NEAREST
};

enum Wrappers
{
	REPEAT = GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE
};

enum FilterOptions
{
	MIN = GL_TEXTURE_MIN_FILTER,
	MAG = GL_TEXTURE_MAG_FILTER
};

enum WrapOptions
{
	WRAP_S = GL_TEXTURE_WRAP_S,
	WRAP_T = GL_TEXTURE_WRAP_T
};

class Texture: public Component
{

public:

	static void GetTexture(const std::string& textureID, Texture& texture);

public:

	Texture();
	Texture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter, GLenum internalFormat, GLenum format, bool clamp, GLenum attachment);

	void InitShit(int width, int height, unsigned char** data, GLenum textureTarget, GLfloat* filter, GLenum* internalFormat, GLenum* format, bool clam, GLenum* attachment);
public:

	void const Bind() const;
	bool Load(const std::string& filename, const std::string& ID);
	void LoadCubeMap(std::vector<std::string> vector, const std::string& ID);
	void const Unbind() const;
	void const Unload(const std::string textureID) const;

public:

	GLint const GetID() const;

public:

	void const SetFilter(FilterOptions const option, Filters const  filter) const;

public:

	void const SetWrapper(WrapOptions const  option, Wrappers const wrapper) const;

public:

	void BindAsRenderTarget();

private:

	static std::map<std::string, Texture>* s_textureMap;

private:

	GLuint m_ID;

	Filters filter;
	GLuint m_frameBuffer;
	GLuint m_renderBuffer;

private:

	int m_width;
	int m_height;

private:

	GLboolean m_isBound;

};
#endif
