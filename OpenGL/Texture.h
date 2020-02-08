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
	NEAREST, BILINEAR, TRILINEAR, MIPMAP_NEAREST, MIPMAP_NEAREST_BILINEAR, MIPMAP_BILINEAR_NEAREST
};

enum Wrappers
{
	REPEAT, MIRRORED_REPEAT, CLAMP_TO_EDGE
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

	void SetMagFilter(Filters f);
	void SetMinFilter(Filters f);

public:

	void SetSWrapper(Wrappers w);
	void SetTWrapper(Wrappers w);

private:

	static std::map<std::string, Texture>* s_textureMap;

private:

	GLuint m_ID;

private:

	GLboolean m_isBound;

};
#endif
