#include "Game.h"
#include "glad/glad.h"
#include "TestState.h"

#include "TheInput.h"
#include "TheScreen.h"

#include <SDL.h>

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
	m_isGameRunning = true;

	TestState state;
	AddGameState(&state);
	

	//Enable depth test
	glEnable(GL_DEPTH_TEST);

	//Enable Fill Mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//Don't show cursor
	SDL_ShowCursor(SDL_DISABLE);

	//Center mouse 
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//----------------------------- GameLoop

	while (m_isGameRunning)
	{
		if (!m_gameStates.empty())
		{

			gamestate_->Update();

			if (!gamestate_->GetIsRunning())
			{
				gamestate_->OnExit();
				m_gameStates.pop_back();
			}

			KeyState keys = TheInput::Instance()->GetKeyStates();

			//If x is pressed Game turns off
			if (keys[SDL_SCANCODE_ESCAPE])
			{
				m_isGameRunning = false;
			}
		}
	}
}

//-------------------------------------------------------------------------------
//Change Game State function
//-------------------------------------------------------------------------------
void Game::ChangeGameState(GameState* gamestate)
{
	//----------------------------- If there is a gamestate, remove it
	if (!m_gameStates.empty())
	{
		RemoveGameState(&m_gameStates.front());
	}

	//Add new gamestate
	AddGameState(gamestate);
}

//-------------------------------------------------------------------------------
//Remove GameState
//-------------------------------------------------------------------------------
void Game::RemoveGameState(GameState* gamestate)
{
	m_gameStates.pop_back();
	gamestate_->OnExit();
}

//-------------------------------------------------------------------------------
//Add GameState
//-------------------------------------------------------------------------------
void Game::AddGameState(GameState* gamestate)
{
	m_gameStates.push_back(*gamestate);

	gamestate_ = gamestate;
	gamestate->Create();
}

//-------------------------------------------------------------------------------
//Exit Game
//-------------------------------------------------------------------------------
void Game::ExitGame()
{
	m_isGameRunning = false;

	TheInput::Instance()->Destroy();
	TheScreen::Instance()->Shutdown();
}
