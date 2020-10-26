#include "Texture.h"
#include "TheDebug.h"
#include <SDL_image.h>
#include <iostream>

//initialize texture map at the very start of the app
std::map<std::string, Texture>* Texture::s_textureMap = new std::map<std::string, Texture>;

//-------------------------------------------------------------------------------
//Get Texture TODO::Check Functionality
//-------------------------------------------------------------------------------
void Texture::GetTexture(const std::string& textureID, Texture& texture)
{
	bool isInMap = false;
	std::map<std::string, Texture>::iterator it;

	it = s_textureMap->find(textureID);

	if (it != s_textureMap->end())
	{
		isInMap = true;
		texture = it->second;
	}

	//Check if texture is in map
	if (isInMap == false)
	{
		std::string tempString = "Texture: " + textureID + " can not be found!";
		TheDebug::Log(tempString, ALERT);
	}
}

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Texture::Texture()
{
	name = "Texture";
	ID = 0;
}


//-------------------------------------------------------------------------------
//Constructor 2
//-------------------------------------------------------------------------------
Texture::Texture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter, GLenum internalFormat, GLenum format, bool clamp, GLenum attachment)
{
	InitStuff(width, height, &data, textureTarget, &filter, &internalFormat, &format, clamp, &attachment);
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Texture::~Texture()
{
}


//-------------------------------------------------------------------------------
//Initialize TODO::Use/create Wrapper class for all gl functions
//-------------------------------------------------------------------------------
void Texture::InitStuff(int width, int height, unsigned char** data, GLenum textureTarget, GLfloat* filter, GLenum* internalFormat, GLenum* format, bool clam, GLenum* attachment)
{

	height = height;
	width = width;
	glGenTextures(1, &ID);

	glBindTexture(textureTarget, ID);

	glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter[0]);
	glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter[0]);

	if (clam)
	{
		glTexParameterf(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	glTexImage2D(textureTarget, 0, internalFormat[0], width, height, 0, format[1], GL_UNSIGNED_BYTE, data);


	GLenum drawBuffers[32];      //32 is the max number of bound textures in OpenGL //Assert to be sure no buffer overrun should occur

	bool hasDepth = false;

	if (attachment[0] == GL_DEPTH_ATTACHMENT)
	{
		drawBuffers[0] = GL_NONE;
		hasDepth = true;
	}
	else
	{
		drawBuffers[0] = attachment[0];
	}


	if (attachment[0] == GL_NONE)
	{
		if (frameBuffer == 0)
		{
			glGenFramebuffers(1, &frameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment[0], textureTarget, ID, 0);
		if (!frameBuffer == 0)
		{
			if (!hasDepth)
			{
				glGenRenderbuffers(1, &renderBuffer);
				glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
			}

			glDrawBuffers(1, drawBuffers);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				std::cerr << "Framebuffer creation failed!" << std::endl;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
void const Texture::Bind() const 
{
	//Bind texture
	glBindTexture(GL_TEXTURE_2D, ID);

	if (ID < 0)
	{
		TheDebug::Log("Texture ID could not be bound", ALERT);
	}
}

//-------------------------------------------------------------------------------
//Load Texture
//-------------------------------------------------------------------------------
bool Texture::Load(const std::string& filename, const std::string& IDRef)
{
	//-----------------------------
	//Check if texture has already been loaded
	//-----------------------------
	bool isInMap = false;
	std::map<std::string, Texture>::iterator it;

	it = s_textureMap->find(IDRef);

	if (it == s_textureMap->end())
	{
	}
	else
	{
		isInMap = true;
		*this = it->second;
	}

	//-----------------------------
	//Load raw image into RAM
	//-----------------------------

	if (isInMap == false)
	{
		//Load the raw image data from file
		SDL_Surface* textureData = IMG_Load(filename.c_str());

		//----------------------------- If image data could not be loaded 

		if (!textureData)
		{
			std::string tempS = "Error loading texture file " + filename;
			TheDebug::Log(tempS, ALERT);

			return false;
		}

		//Extract the raw mage data and store in variables for use below (easier)
		GLsizei width = textureData->w;
		GLsizei height = textureData->h;
			
		Uint8* pixels = (Uint8*)textureData->pixels;
		Uint8 depth = textureData->format->BytesPerPixel;
		GLint format = (depth == 4) ? GL_RGBA : GL_RGB;


		//----------------------------
		//Create texture object in VRAM
		//----------------------------

		//Create the teture ID for our texture object(VRAM)
		glGenTextures(1, &ID);

		//Bind the texture ID
		glBindTexture(GL_TEXTURE_2D, ID);

		//Set default filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//Create the texture object in VRAM using the raw data extracted above
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

		//Create mipmap for textures
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		//Release RAM image
		SDL_FreeSurface(textureData);

		//Add the new texture image to the map
		s_textureMap->insert(std::pair<std::string, Texture>(IDRef, *this));
	}

	return true;
}

//-------------------------------------------------------------------------------
//Load CubeMap Texture TODO::Explain Functionality
//-------------------------------------------------------------------------------
void Texture::LoadCubeMap(std::vector<std::string> vector, const std::string& IDRef)
{
//-----------------------------
//Check if texture has already been loaded
//-----------------------------
	bool isInMap = false;
	std::map<std::string, Texture>::iterator it;

	it = s_textureMap->find(IDRef);

	if (it != s_textureMap->end())
	{
		isInMap = true;
		*this = it->second;
	}

	//-----------------------------
	//Load raw image into RAM
	//-----------------------------

	if (isInMap == false)
	{
		//----------------------------
		//Create texture object in VRAM
		//----------------------------

		//Create the teture ID for our texture object(VRAM)
		glGenTextures(1, &ID);

		//Bind the texture ID
		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

		int width;
		int height;
		int nrComponents;

		for (unsigned int i = 0; i < vector.size(); i++)
		{
			SDL_Surface* data = IMG_Load(vector[i].c_str());

			width = data->w;
			height = data->h;
			Uint8* pixels = (Uint8*)data->pixels;
			Uint8 depth = data->format->BytesPerPixel;
			GLint format = (depth == 4) ? GL_RGBA : GL_RGB;

			if (data)
			{
				//Create the texture object in VRAM using the raw data extracted above
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

				SDL_FreeSurface(data);
			}
			else
			{
				std::string tempString = "Cubemap texture failed to load at path: " + vector[i];
				TheDebug::Log(tempString, ALERT);

				SDL_FreeSurface(data);
			}
		}
		//Set default filtering and wraping options
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


		//Add the new texture image to the mapx
		s_textureMap->insert(std::pair<std::string, Texture>(IDRef, *this));
	}
}

//-------------------------------------------------------------------------------
//Unbind Texture
//-------------------------------------------------------------------------------
void const Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

//-------------------------------------------------------------------------------
//Delete textures/Unload them from memory
//-------------------------------------------------------------------------------
void const Texture::Unload(const std::string textureID) const
{
	// Loop and check id in the map
	glDeleteTextures(1, &ID);
}

//-------------------------------------------------------------------------------
//return ID
//-------------------------------------------------------------------------------
GLint const Texture::GetID() const
{
	return ID;
}

//-------------------------------------------------------------------------------
//Set filter TODO::Check Functionality/Wrap gl functions
//-------------------------------------------------------------------------------
void const Texture::SetFilter(FilterOptions const option, Filters const filter) const
{
	if (isBound)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, option, filter);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		if (option == MIN)
		{
			TheDebug::Log("Need to bind Texture first, before setting Minification filter", ALERT);
		}
		else
		{
			TheDebug::Log("Need to bind Texture first, before setting Magnification filter", ALERT);
		}
	}
}

//-------------------------------------------------------------------------------
//Set Wrapper filter TODO::Check Functionality/Wrap gl functions
//-------------------------------------------------------------------------------
void const Texture::SetWrapper(WrapOptions const option, Wrappers const wrapper) const
{
	if (isBound)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, option, wrapper);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		if (option == WRAP_S)
		{
			TheDebug::Log("Need to bind Texture first, before setting S Wrapper", ALERT);
		}
		else
		{
			TheDebug::Log("Need to bind Texture first, before setting T Wrapper", ALERT);
		}
	}
}

//-------------------------------------------------------------------------------
//Bind as Render Target TODO::Check Functionality/Wrap gl functions
//-------------------------------------------------------------------------------
void Texture::BindAsRenderTarget()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}
