#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState
{

public:

	GameState() {}
	~GameState() {}

public:

	virtual void Create() {}
	virtual void Update() {} 
	virtual void OnExit() {}

protected:

	bool isRunning;

public:

	bool GetIsRunning();
	void SetIsRunning(bool& isrunning);
};

#endif