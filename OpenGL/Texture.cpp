#include "Texture.h"
#include "TheDebug.h"
#include <SDL_image.h>
#include <iostream>

//initialize texture map at the very start of the app
std::map<std::string, Texture>* Texture::s_textureMap = new std::map<std::string, Texture>;

//-------------------------------------------------------------------------------
//Get Texture
//-------------------------------------------------------------------------------
void Texture::GetTexture(const std::string& textureID, Texture& texture)
{
	bool isInMap = false;

	//Check if texture is in the map
	for (auto it = s_textureMap->begin(); it != s_textureMap->end(); it++)
	{
		if (it->first == textureID)
		{
			texture = it->second;
			isInMap = true;
		}
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
	m_ID = 0;
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
void Texture::Bind()
{
	//Bind texture
	glBindTexture(GL_TEXTURE_2D, m_ID);

	if (m_ID < 0)
	{
		TheDebug::Log("Texture ID could not be bound", ALERT);
	}
}

//-------------------------------------------------------------------------------
//Load Texture
//-------------------------------------------------------------------------------
bool Texture::Load(const std::string& filename, const std::string& ID)
{

	//-----------------------------
	//Check if texture has already been loaded
	//-----------------------------
	bool isInMap = false;

	for (auto it = s_textureMap->begin(); it != s_textureMap->end(); it++)
	{
		if (it->first == ID)
		{
			*this = it->second;

			isInMap = true;
		}
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
		glGenTextures(1, &m_ID);

		//Bind the texture ID
		glBindTexture(GL_TEXTURE_2D, m_ID);

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
		s_textureMap->insert(std::pair<std::string, Texture>(ID, *this));
	}

	return true;
}

//-------------------------------------------------------------------------------
//Load CubeMap Texture
//-------------------------------------------------------------------------------
void Texture::LoadCubeMap(std::vector<std::string> vector, const std::string& ID)
{
	//-----------------------------
//Check if texture has already been loaded
//-----------------------------
	bool isInMap = false;

	for (auto it = s_textureMap->begin(); it != s_textureMap->end(); it++)
	{
		if (it->first == ID)
		{
			*this = it->second;

			isInMap = true;
		}
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
		glGenTextures(1, &m_ID);

		//Bind the texture ID
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);

		int width;
		int height;
		int nrComponents;
		for (unsigned int i = 0; i < vector.size(); i++)
		{
			SDL_Surface* data = IMG_Load(vector[i].c_str());

			width = data->w;
			height = data->h;

			if (data)
			{
				//Create the texture object in VRAM using the raw data extracted above
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

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
		s_textureMap->insert(std::pair<std::string, Texture>(ID, *this));
	}
}

//-------------------------------------------------------------------------------
//Unbind Texture
//-------------------------------------------------------------------------------
void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

//-------------------------------------------------------------------------------
//Delete textures/Unload them from memory
//-------------------------------------------------------------------------------
void Texture::Unload(const std::string textureID)
{
	// Loop and check id in the map
	glDeleteTextures(1, &m_ID);
}

//-------------------------------------------------------------------------------
//return ID
//-------------------------------------------------------------------------------
GLint Texture::GetID()
{
	return m_ID;
}

//-------------------------------------------------------------------------------
//Set filter
//-------------------------------------------------------------------------------
void const Texture::SetFilter(FilterOptions const option, Filters const filter) const
{
	if (m_isBound)
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
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
//Set S Wrapper filter
//-------------------------------------------------------------------------------
void Texture::SetSWrapper(Wrappers w)
{
	//Check if texture is bound
	if (m_isBound)
	{
		//Check which Wrapper to use for S variable
		switch (w)
		{
		case REPEAT:

			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glBindTexture(GL_TEXTURE_2D, 0);

			break;

		case MIRRORED_REPEAT:

			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glBindTexture(GL_TEXTURE_2D, 0);

			break;

		case CLAMP_TO_EDGE:

			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, 0);

			break;

		default:

			break;
		}
	}
	else
	{
		TheDebug::Log("Need to bind Texture first, before setting S Wrapper", ALERT);
	}
}

//-------------------------------------------------------------------------------
//Set T Wrapper filter
//-------------------------------------------------------------------------------
void Texture::SetTWrapper(Wrappers w)
{
	//Check if texture is bound
	if (m_isBound)
	{
		//Check which Wrapper to use for T variable
		switch (w)
		{
		case REPEAT:
	
			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBindTexture(GL_TEXTURE_2D, m_ID);

			break;
	
		case MIRRORED_REPEAT:
	
			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			glBindTexture(GL_TEXTURE_2D, 0);

			break;
	
		case CLAMP_TO_EDGE:
	
			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, 0);

			break;
	
		default:
	
			break;
		}
	}
	else
	{
		TheDebug::Log("Need to bind Texture first, before setting T Wrapper", ALERT);
	} 
}

