#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "TheInput.h"
#include "EditorInterface.h"
#include <vector>
#include "Texture.h"

class Game
{
private:

	Game() {}
	Game(const Game&);
	Game& operator=(Game&);

	~Game();

public:

	static Game* Instance();

public:


	void Run();
	void ChangeGameState(GameState& gamestate);
	void RemoveGameState(GameState& gamestate);
	void AddGameState(GameState& gamestate);

	void ExitGame();

public:

	GameState* GetCurrentScene() const;

private:

	int currentStateIndex;

private:

	std::vector<GameState*> gameStates;

private:

	EditorInterface* editorInterface;

private:

	bool isGameRunning;
	bool isLoading;

private:

	KeyState keys;
};
#endif

