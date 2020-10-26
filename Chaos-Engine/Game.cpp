#include "Game.h"
#include "glad/glad.h"
#include "TestState.h"
#include "ShadowDemoState.h"
#include "ParallaxDemoState.h"

#include "TheInput.h"
#include "TheScreen.h"
#include "TheDebug.h"
#include "TheShader.h"

#include <SDL.h>

Game::~Game()
{
	delete editorInterface;
}

//-------------------------------------------------------------------------------
//Create game statically (only happens once) and return it
//-------------------------------------------------------------------------------
Game* Game::Instance()
{
	static Game* game = new Game;

	return game;
}

//-------------------------------------------------------------------------------
//Run Game function
//-------------------------------------------------------------------------------
void Game::Run()
{
	currentStateIndex = 0;
	isGameRunning = true;

	//Initialise Screen manager
	TheScreen::Instance()->Initialize();

	//Create interface
	editorInterface = new EditorInterface;

	//Initialise Input manager
	TheInput::Instance()->Initialize();

	//Create Shaders
	TheShader::Instance()->CreateShaders("Lightless.vert", "Lightless.frag");
	TheShader::Instance()->CreateShaders("LightMap.vert", "LightMap.frag");
	TheShader::Instance()->CreateShaders("Lighting.vert", "Lighting.frag");
	TheShader::Instance()->CreateShaders("Toon.vert", "Toon.frag");
	TheShader::Instance()->CreateShaders("ShadowMapGen.vert", "ShadowMapGen.frag");
	TheShader::Instance()->CreateShaders("ShadowMapping.vert", "ShadowMapping.frag");
	TheShader::Instance()->CreateShaders("NormalMapping.vert", "NormalMapping.frag");
	TheShader::Instance()->CreateShaders("Cubemap.vert", "Cubemap.frag");
	TheShader::Instance()->CreateShaders("Skybox.vert", "Skybox.frag");


	//Initialise Shader manager
	TheShader::Instance()->Initialize();
	
	//glEnable(GL_DEPTH_CLAMP);

	//Enable Fill Mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Add GameStateq
	TestState state;
	ShadowDemoState state2;
	ParallaxDemoState state3;
	//Put this below to check Parallax state
	AddGameState(state3);

	//Put this below to check Shadow state
	AddGameState(state2);

	//Scene Playing
	AddGameState(state);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	//GameLoop
	while (isGameRunning)
	{
		if (!gameStates.empty())
		{
			TheScreen::Instance()->Clear();

			//Clear the buffer so the next iteration of data can be loaded in
			//glClear(GL_DEPTH_BUFFER_BIT);

			//Start Imgui Frame
			TheScreen::Instance()->ImguiFrame();

			gameStates[currentStateIndex]->Update();

			if (!gameStates[currentStateIndex]->GetIsRunning())
			{
				gameStates[currentStateIndex]->OnExit();
				gameStates.pop_back();
			}

			KeyState keys = TheInput::Instance()->GetKeyStates();

			//Set To Editor Mode if M click is pressed
			if (keys[SDL_SCANCODE_P])
			{
				if (TheInput::Instance()->GetKeyDown())
				{
					if (TheInput::Instance()->GetEditorMode())
					{
						TheInput::Instance()->SetEditorMode(false);

						//Don't show cursor
						SDL_ShowCursor(SDL_DISABLE);

						//Center mouse 
						SDL_SetRelativeMouseMode(SDL_TRUE);
					}
					else
					{
						TheInput::Instance()->SetEditorMode(true);

						//Don't show cursor
						SDL_ShowCursor(SDL_ENABLE);

						//Center mouse 
						SDL_SetRelativeMouseMode(SDL_FALSE);
					}
				}
			}

			if (keys[SDL_SCANCODE_ESCAPE])
			{
				isGameRunning = false;
			}

			//Check for OpenGL Errors
			TheDebug::Instance()->CheckOpenGLErrors();

			if (TheInput::Instance()->GetEditorMode())
			{
				//Draw Editor
				editorInterface->DrawEditor();
			}

			// Render ImGui Windows
			TheScreen::Instance()->ImguiRender();

			//Swap Buffers
			TheScreen::Instance()->SwapBuffer();
			
			if (keys[SDL_SCANCODE_N])
			{
				if (isLoading == false)
				{
					isLoading = true;
					bool tempBool = false;
					gameStates[currentStateIndex]->SetIsRunning(tempBool);

					if (currentStateIndex == gameStates.size() - 1)
					{
						currentStateIndex = 0;
					}
					else
					{
						currentStateIndex ++;
					}
					
					tempBool = true;
					gameStates[currentStateIndex]->SetIsRunning(tempBool);
				}
			}
			else
			{
				isLoading = false;
			}
		}
	}
}

//-------------------------------------------------------------------------------
//Change Game State function
//-------------------------------------------------------------------------------
void Game::ChangeGameState(GameState& gamestate)
{
	//If there is a gamestate, remove it
	if (!gameStates.empty())
	{
		RemoveGameState(*gameStates.front());
	}

	//Add new gamestate
	AddGameState(gamestate);
}

//-------------------------------------------------------------------------------
//Remove GameState
//-------------------------------------------------------------------------------
void Game::RemoveGameState(GameState& gamestate)
{
	gameStates.pop_back();
	gameStates[currentStateIndex]->OnExit();
}

//-------------------------------------------------------------------------------
//Add GameState
//-------------------------------------------------------------------------------
void Game::AddGameState(GameState& gamestate)
{
	gameStates.push_back(&gamestate);
	currentStateIndex = gameStates.size() - 1;
	gameStates[currentStateIndex]->Create();
}

//-------------------------------------------------------------------------------
//Exit Game
//-------------------------------------------------------------------------------
void Game::ExitGame()
{
	isGameRunning = false;

	TheInput::Instance()->Destroy();
	TheScreen::Instance()->Shutdown();
	TheShader::Instance()->DestroyShader();
}

//-------------------------------------------------------------------------------
//Get Current Scene
//-------------------------------------------------------------------------------
GameState* Game::GetCurrentScene() const
{
	return gameStates[currentStateIndex];
}
