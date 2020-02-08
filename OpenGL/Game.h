#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "TheInput.h"
#include <vector>

class Game
{
private:

	Game() {}
	Game(const Game&);
	Game& operator=(Game&);

public:

	static Game* Instance();

public:

	void Run();
	void ChangeGameState(GameState* gamestate);
	void RemoveGameState(GameState* gamestate);
	void AddGameState(GameState* gamestate);

	void ExitGame();

private:

	GameState* gamestate_;

private:

	std::vector<GameState> m_gameStates;

private:

	bool m_isGameRunning;

private:

	KeyState keys;
};
#endif

