#include <iostream>

#include "Tools.h"
#include "TheDebug.h"
#include "TheScreen.h"

//-------------------------------------------------------------------------------
//Create the Screen manager statically (only happens once) and return it
//-------------------------------------------------------------------------------
TheScreen* TheScreen::Instance()
{
	static TheScreen* s_screenManager = new TheScreen;

	return s_screenManager;
}

//-------------------------------------------------------------------------------
//Create input manager statically (only happens once) and return it
//-------------------------------------------------------------------------------
void TheScreen::Initialize()
{
	//Print Screen Opener
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

	std::cout << "                .----.' " << std::endl;
	std::cout << "    .---------. | == |' " << std::endl;
	std::cout << "    |.-'''''-.| |----| '" << std::endl;
	std::cout << "    ||Chaos's|| | == |' " << std::endl;
	std::cout << "    ||Engine || |----|' " << std::endl;
	std::cout << "    |'-.....-'| |::::|' " << std::endl;
	std::cout << "    `'')---(''` |___.|' " << std::endl;
	std::cout << "   /:::::::::::\'  _  ''" << std::endl;
	std::cout << "  /:::=======:::\`\`\   " << std::endl;
	std::cout << "  `'''''''''''''`  '-'  " << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	//----------------------------------------------------------
	//Screen config
	//----------------------------------------------------------

	//Open and read file
	OpenConfigFile();

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL not initialized!" << std::endl;
	}

	//Set RGBA buffer sizes and the total buffer size to be able to have 32-bit color
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, bufferSize);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, bufferSize);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bufferSize);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, bufferSize);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, totalBufferSize);

	//Check if it's Double Buffer
	if (isDoubleBuffer)
	{
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	}

	//Set a compatibility OpenGL context depending on which one is chosen;
	if (isCompatabilityMode)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}

	//Set OpenGL to version chosen which is a safe version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	//Create Window
	window = SDL_CreateWindow("Chaos-Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

	//Check if window was opened correctly
	if (!window)
	{
		TheDebug::Log("WINDOW can not be found", ALERT);
		system("pause");
	}

	//Check if window is fullscreen
	if (isFullscreen == true)
	{
		SDL_SetWindowFullscreen(window, SDL_TRUE);
	}
	else
	{
		SDL_SetWindowFullscreen(window, SDL_FALSE);
	}

	//Check if window can be resizable
	if (isResizable)
	{
		SDL_SetWindowResizable(window, SDL_TRUE);
	}

	//Check if window is bordered
	if (isBorderless)
	{
		SDL_SetWindowBordered(window, SDL_TRUE);
	}

	//Create Context and check if opened correctly
	context = SDL_GL_CreateContext(window);

	if (!context)
	{
		TheDebug::Log("CONTEXT can not be found", ALERT);
		system("pause");
	} 

	//Load Glad
	if (!gladLoadGL())
	{
		TheDebug::Log("GLAD can not be found", ALERT);
		system("pause");
	}

	//Display profile 
	DisplayProfile();

	//Create IMGUI context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = ImGui::GetIO(); (void)io;
	ImGui_ImplSDL2_InitForOpenGL(window, context);

	// Setup Dear ImGui Dark style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	ImGui_ImplOpenGL3_Init();

	//Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//-------------------------------------------------------------------------------
//Clear the buffer so the next iteration of data can be loaded in
//-------------------------------------------------------------------------------
void TheScreen::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


//-------------------------------------------------------------------------------
//Swap Buffer
//-------------------------------------------------------------------------------
void TheScreen::SwapBuffer()
{
	SDL_GL_SwapWindow(window);
}

//-------------------------------------------------------------------------------
//Open Config file
//-------------------------------------------------------------------------------
void TheScreen::OpenConfigFile()
{
	//Open Text file
	configTextFile.open("./Data/Config.txt", std::ios_base::in);

	//----------------------------------------------------------
	//Open text file and check config data
	//----------------------------------------------------------

	//Declare token
	char token = '=';

	//Check if file is open
	if (configTextFile.is_open())
	{
		//Loop until text file is fully read
		while (!configTextFile.eof())
		{
			//Create temporary string and store corresponsive line
			std::string textString;
			std::getline(configTextFile, textString);

			//Print Config information
			if (textString[0] != '/')
			{
				TheDebug::Log(textString, SUCCESS);
			}

			//Parse each line 
			ParseText(textString, token, textMap);
		}

		//Set Window Width
		windowWidth = std::stoi(textMap["Width"]); 

		//Set Window Height
		windowHeight = std::stoi(textMap["Height"]);

		//Set Buffer Size
		bufferSize = std::stoi(textMap["BufferSize"]);

		//Set Total Buffer size
		totalBufferSize = std::stoi(textMap["TotalBufferSize"]);

		//Set Major version
		openGLMajorVersion = std::stoi(textMap["OpenGLMajorVersion"]);

		//Set Minor version
		openGLMinorVersion = std::stoi(textMap["OpenGLMinorVersion"]);

		//----------------------------------------------------------
		//Open text file and check config data
		//----------------------------------------------------------
		for (auto const& str : textMap)
		{
			//Check and set fullscreen flag
			if (str.first == "Fullscreen")
			{
				if (str.second == "true")
				{
					isFullscreen = true;
				}
				else
				{
					isFullscreen = false;
				}
			}

			//Check and set window resizable
			else if (str.first == "Resizable")
			{
				if (str.second == "true")
				{
					isResizable = true;
				}
				else
				{
					isResizable = false;
				}
			}

			//Check and set window borderless
			else if (str.first == "Borderless")
			{
				if (str.second == "true")
				{
					isBorderless = true;
				}
				else
				{
					isBorderless = false;
				}
			}

			//Check and Set Double Buffer
			else if (str.first == "DoubleBuffer")
			{
				if (str.second == "true")
				{
					isDoubleBuffer = true;
				}
				else
				{
					isDoubleBuffer = false;
				}
			}

			//Check and Set Compatability Mode or Core Mode
			else if (str.first == "CompatabilityMode")
			{
				if (str.second == "true")
				{
					isCompatabilityMode = true;
				}
				else
				{
					isCompatabilityMode = false;
				}
			}
		}
	}
	else
	{
		TheDebug::Log("Could not open config file", ALERT);
	}
}

//-------------------------------------------------------------------------------
//Get Screen size
//-------------------------------------------------------------------------------
void TheScreen::GetScreenSize(int& width, int& height)
{
	width = windowWidth;
	height = windowHeight;
}

//-------------------------------------------------------------------------------
//x = height, y = width
//-------------------------------------------------------------------------------
glm::vec2 TheScreen::GetScreenSize()
{
	return glm::vec2(windowWidth, windowHeight);
}

//-------------------------------------------------------------------------------
//Delete stuff for when application is closed
//-------------------------------------------------------------------------------
void TheScreen::Shutdown()
{
	//Imgui Shutdown
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//SDL Shutdown
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//-------------------------------------------------------------------------------
//Display supported OpenGL hardware
//-------------------------------------------------------------------------------
void TheScreen::DisplayProfile()
{
	//Display graphics card profile
	std::cout << "Graphics manufacturer: " << (const char*)(glGetString(GL_VENDOR)) << std::endl;
	std::cout << "Graphics card: " << (const char*)(glGetString(GL_RENDERER)) << std::endl;
	std::cout << "OpenGL version: " << (const char*)(glGetString(GL_VERSION)) << std::endl;
	std::cout << "GLSL version: " << (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
}

//-------------------------------------------------------------------------------
//Check if OpenGL is supported and display all the extension
//-------------------------------------------------------------------------------
void TheScreen::DisplayExtensions()
{

	//Check if graphic's card are supported
	if (!glGetStringi)
	{
		TheDebug::Log("glGetStringi graphic card's drivers not supported.", ALERT);
		system("pause");
	}
	else
	{
		//Get total extensions 
		GLint totalExtensions = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

		//List all extensions
		for (int i = 0; i < totalExtensions; i++)
		{
			std::cout << "Extension #" << i + 1 << (const char*)glGetStringi(GL_EXTENSIONS, i) << std::endl;
		}
	}
}

//-------------------------------------------------------------------------------
//IMGUI Frame
//-------------------------------------------------------------------------------
void TheScreen::ImguiFrame()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);
	ImGui::NewFrame();
}

//-------------------------------------------------------------------------------
//IMGUI Render
//-------------------------------------------------------------------------------
void TheScreen::ImguiRender()
{
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//-------------------------------------------------------------------------------
//Bind As Render Target
//-------------------------------------------------------------------------------
void TheScreen::BindAsRenderTarget()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, windowWidth, windowHeight);
}

