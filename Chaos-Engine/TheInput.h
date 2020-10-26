#ifndef THEINPUT_H
#define THEINPUT_H

#include <SDL.h>
#include <vector>
#include <glm.hpp>

typedef const Uint8* KeyState;

class TheInput
{

public:

	static TheInput* Instance();

public:
	
	void Initialize();
	void Update();

public:

	void initialiseJoysticks();
	void Destroy();

public:

	int GetJoystickXValue(const int& joy, const int& stick);
	int GetJoystickYValue(const int& joy, const int& stick);

public:

	char GetKeyUp() const;
	char GetKeyDown() const;

	bool GetIsXClicked() const;
	bool GetJoysticksInitialized() const;
	bool GetIsControllerActive() const;

	int GetMouseMotionX() const;
	int GetMouseMotionY() const;

	int GetMousePositionX() const;
	int GetMousePositionY() const;

	KeyState GetKeyStates() const;

	glm::vec2 GetMotion() const;

	bool GetMouseButtonDown(const int& mouseid) const;

public:

	bool GetEditorMode() const;
	void SetEditorMode(const bool& value);

public:

	void SetMotionX(const int& value);
	void SetMotionY(const int& value);

private:

	TheInput() {}
	TheInput(const TheInput&);
	TheInput& operator=(TheInput&);


private:

	bool isKeyDown;
	bool isXClicked;
	bool isLeftButtonDown;
	bool isRightButtonDown;
	bool isMiddleButtonDown;

	bool areJoysticksDown;
	bool areJoysticksInitialised;

	bool isControllerActive;

	char keyUp;
	char keyDown;
	char hatDown;

	int mouseMotionX;
	int mouseMotionY;
	
	int mousePositionX;
	int mousePositionY;

	glm::vec2 motion;

	const int JOYSTICKDEADZONE = 8000;

private:

	bool isEditorMode;

private:

	std::vector<char> keyboardInput;
	std::vector<SDL_Joystick*> joysticks;

private:

	KeyState keyStates;
	SDL_Joystick* joystick;

	std::vector<std::pair<glm::vec2*, glm::vec2*>> joystickValues;
};

#endif // !THEINPUTMANAGER_H

