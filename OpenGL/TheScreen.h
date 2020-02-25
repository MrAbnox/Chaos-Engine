#ifndef THESCREEN_H
#define THESCREEN_H


#include "glad/glad.h"

#include <SDL.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <map>

class TheScreen
{
public:

	static TheScreen* Instance();

	void Initialize();
	void Clear();
	void SwapBuffer();

public:

	void OpenConfigFile();

public:

	void GetScreenSize(int& width, int& height);

public:

	void Shutdown();

private:

	SDL_Window* window;
	SDL_GLContext context;
	SDL_Joystick* joystick;

private:

	TheScreen() {};
	TheScreen(const TheScreen&);
	TheScreen& operator=(const TheScreen&);

private:

	void DisplayProfile();
	void DisplayExtensions();

private:

	std::ifstream m_configTextFile;

private:

	std::map<std::string, std::string> m_textMap;

private:

	bool m_isResizable;
	bool m_isFullscreen;
	bool m_isBorderless;
	bool m_isDoubleBuffer;
	bool m_isCompatabilityMode;

	int m_bufferSize;
	int m_windowWidth;
	int m_doubleBuffer;
	int m_windowHeight;
	int m_totalBufferSize;
	int m_openGLMajorVersion;
	int m_openGLMinorVersion;

	std::string m_windowName;
};

#endif