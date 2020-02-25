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

	int xvalue(const int& joy, const int& stick);
	int yvalue(const int& joy, const int& stick);

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

public:

	bool GetDevMode() const;
	void SetDevMode(const bool& value);

public:

	void SetMotionX(const int& value);
	void SetMotionY(const int& value);

private:

	TheInput() {}
	TheInput(const TheInput&);
	TheInput& operator=(TheInput&);


private:

	bool m_isKeyDown;
	bool m_isXClicked;
	bool m_isLeftButtonDown;
	bool m_isRightButtonDown;
	bool m_isMiddleButtonDown;

	bool m_areJoysticksDown;
	bool m_areJoysticksInitialised;

	bool m_isControllerActive;

	char m_keyUp;
	char m_keyDown;
	char m_hatDown;

	int m_mouseMotionX;
	int m_mouseMotionY;
	
	int m_mousePositionX;
	int m_mousePositionY;

	glm::vec2 m_motion;

	const int m_JOYSTICKDEADZONE = 8000;

private:

	bool m_isDevMode;

private:

	std::vector<char> m_keyboardInput;
	std::vector<SDL_Joystick*> m_joysticks;

private:

	KeyState m_keyStates;
	SDL_Joystick* joystick;

	std::vector<std::pair<glm::vec2*, glm::vec2*>> m_joystickValues;
};

#endif // !THEINPUTMANAGER_H

