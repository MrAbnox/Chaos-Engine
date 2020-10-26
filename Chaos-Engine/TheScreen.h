#ifndef THESCREEN_H
#define THESCREEN_H


#include "glad/glad.h"

#include <SDL.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <map>
#include <glm.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

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
	glm::vec2 GetScreenSize();

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

public:

	void ImguiFrame();
	void ImguiRender();

public:

	void BindAsRenderTarget();

private:

	std::ifstream configTextFile;

private:

	std::map<std::string, std::string> textMap;

private:

	ImGuiIO io;

private:

	bool isResizable;
	bool isFullscreen;
	bool isBorderless;
	bool isDoubleBuffer;
	bool isCompatabilityMode;

	int bufferSize;
	int windowWidth;
	int doubleBuffer;
	int windowHeight;
	int totalBufferSize;
	int openGLMajorVersion;
	int openGLMinorVersion;

	std::string windowName;
};

#endif