#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad.h"

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
	WRAP_S,
	WRAP_T
};

class Texture
{

public:

	static void GetTexture(const std::string& textureID, Texture& texture);

public:

	Texture();

public:

	void Bind();
	bool Load(const std::string& filename, const std::string& ID);
	void LoadCubeMap(std::vector<std::string> vector, const std::string& ID);
	void Unbind();
	void Unload(const std::string textureID);

public:

	GLint GetID();

public:

	void const SetFilter(FilterOptions const option, Filters const  filter) const;

public:

	void SetSWrapper(Wrappers w);
	void SetTWrapper(Wrappers w);

private:

	static std::map<std::string, Texture>* s_textureMap;

private:

	GLuint m_ID;

	Filters filter;

private:

	GLboolean m_isBound;

};
#endif
