#include "TheInput.h"
#include "Game.h"
#include <iostream>

//-------------------------------------------------------------------------------
//Create the Input manager statically (only happens once) and return it
//-------------------------------------------------------------------------------
TheInput* TheInput::Instance()
{
	static TheInput* inputManager = new TheInput;

	return inputManager;
}

//-------------------------------------------------------------------------------
//Create the Input manager statically (only happens once) and return it
//-------------------------------------------------------------------------------
void TheInput::Initialize()
{
	m_isControllerActive = false;

	initialiseJoysticks();

	m_areJoysticksDown = false;
}

//-------------------------------------------------------------------------------
//Update Input manager, so keystates are recognized
//-------------------------------------------------------------------------------
void TheInput::Update()
{

	int SDL_ShowCursor(0);

	//----------------------------------------------------------
	//Initialize Values
	//----------------------------------------------------------

	//==========================================================

	SDL_Event events;

	m_keyDown = 0;

	m_mouseMotionX = 0;
	m_mouseMotionY = 0;

	//==========================================================

	//----------------------------- Get the array of keys

	m_keyStates = SDL_GetKeyboardState(nullptr);

	//----------------------------------------------------------
	//Update Input manager, so keystates are recognized
	//----------------------------------------------------------

	while (SDL_PollEvent(&events))
	{
		//----------------------------- If there's input events
		switch (events.type)
		{

			//-----------------------------------
			//If x is press on window close app
			//-----------------------------------
			case SDL_QUIT:
			{
				m_isXClicked = true;
				Game::Instance()->ExitGame();

				break;
			}

			//-----------------------------------
			//Check if key is down, set flag true
			//-----------------------------------
			case SDL_KEYDOWN:
			{
				m_isControllerActive = false;

				m_keyDown = events.key.keysym.sym;
				m_isKeyDown = true;

				//----------------------------- Check if back space key is pressed, if yes delete char in the back from the vector

				if (events.key.keysym.sym = SDLK_BACKSPACE && m_keyboardInput.size() > 0)
				{
					m_keyboardInput.pop_back();
				}

				//----------------------------- Check if the key pressed is not an empty space, if yes add it to the vector

				else if (events.key.keysym.sym != SDLK_RETURN)
				{
					m_keyboardInput.push_back(m_keyDown);
				}

				break;
			}

			//-----------------------------------
			//Check if key is up, set flag false
			//-----------------------------------
			case SDL_KEYUP:
			{
				m_isControllerActive = false;

				m_keyUp = events.key.keysym.sym;
				m_isKeyDown = false;

				break;

			}

			//----------------------------------- 
			//Record mouse motion and position
			//-----------------------------------
			case SDL_MOUSEMOTION:
			{
				m_isControllerActive = false;

				m_mouseMotionX = events.motion.xrel;
				m_mouseMotionY = events.motion.yrel;

				m_mousePositionX = events.motion.x;
				m_mousePositionY = events.motion.y;

				break;
			}

			//-----------------------------------
			//Check Joysticks axis motion
			//-----------------------------------
			case SDL_JOYAXISMOTION:
			{
				//Get which controller
				int whichOne = events.jaxis.which;

				//Left stick move left or right
				if (events.jaxis.axis == 0)
				{
					m_isControllerActive = true;

					if (events.jaxis.value > m_JOYSTICKDEADZONE)
					{
						m_joystickValues[whichOne].first->x = 1;
					}
					else if (events.jaxis.value < -m_JOYSTICKDEADZONE)
					{
						m_joystickValues[whichOne].first->x = -1;
					}
					else
					{
						m_joystickValues[whichOne].first->x = 0;
					}
				}

				//Left stick move up or down
				if (events.jaxis.axis == 1)
				{
					m_isControllerActive = true;

					if (events.jaxis.value > m_JOYSTICKDEADZONE)
					{
						m_joystickValues[whichOne].first->y = 1;
					}
					else if (events.jaxis.value < -m_JOYSTICKDEADZONE)
					{
						m_joystickValues[whichOne].first->y = -1;
					}
					else
					{
						m_joystickValues[whichOne].first->y = 0;
					}
				}

				//Right stick move left or right
				if (events.jaxis.axis == 3)
				{
					m_isControllerActive = true;

					if (events.jaxis.value > m_JOYSTICKDEADZONE)
					{
						events.jaxis.value = 0;
						m_joystickValues[whichOne].second->x = 1;
					}
					else if (events.jaxis.value < -m_JOYSTICKDEADZONE)
					{
						events.jaxis.value = 0;
						m_joystickValues[whichOne].second->x = -1;
					}
					else
					{
						events.jaxis.value = 0;
						m_joystickValues[whichOne].second->x = 0;
					}
				}

				//Right stick move up or down
				if (events.jaxis.axis == 4)
				{

					m_isControllerActive = true;

					if (events.jaxis.value > m_JOYSTICKDEADZONE)
					{
						events.jaxis.value = 0;
						m_joystickValues[whichOne].second->y = 1;
					}
					else if (events.jaxis.value < -m_JOYSTICKDEADZONE)
					{
						events.jaxis.value = 0;
						m_joystickValues[whichOne].second->y = -1;
					}
					else
					{
						events.jaxis.value = 0;
						m_joystickValues[whichOne].second->y = 0;
					}
				}

				break;
			}

			case SDL_JOYBUTTONDOWN:
			{
				m_isControllerActive = true;		
			}

			case SDL_JOYHATMOTION:
			{
				m_isControllerActive = true;
				m_hatDown = events.jhat.hat;
			}
		}	
	}
}

//-------------------------------------------------------------------------------
//Initialise Joysticks
//-------------------------------------------------------------------------------
void TheInput::initialiseJoysticks()
{
	//----------------------------- Check if joystick substystem has been initialised

	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	//----------------------------- Check if there are joysticks available
	if (SDL_NumJoysticks > 0)
	{
		//----------------------------- Loop through joysticks, open them and add them to vector

		for (size_t i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			m_joysticks.push_back(joy);

			m_joystickValues.push_back(std::make_pair(new glm::vec2(0, 0), new glm::vec2(0, 0)));
		}
	

		//----------------------------- Start listening for Joystick events

		SDL_JoystickEventState(SDL_ENABLE);

		//----------------------------- Set joysticks flag to true and output amount of joysticks

		if (m_joysticks.size() > 0)
		{
			m_areJoysticksInitialised = true;
		}
		else
		{
			m_areJoysticksInitialised = false;
		}

		std::cout << "Initialised: " << m_joysticks.size() << " Joystick(s)" << std::endl;
	}
	else
	{
		m_areJoysticksInitialised = false;
	}
}

//-------------------------------------------------------------------------------
//Clean Function(close Joysticks)
//-------------------------------------------------------------------------------
void TheInput::Destroy()
{
	if (m_areJoysticksInitialised)
	{
		for (size_t i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

int TheInput::xvalue(const int& joy, const int& stick)
{
	if (m_joystickValues.size() > 0)
	{	
		if (stick == 1)
		{
			return m_joystickValues[joy].first->x;
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->x;
		}
	}

	return 0;
}

int TheInput::yvalue(const int& joy, const int& stick)
{
	if (stick == 1)
	{
		return m_joystickValues[joy].first->y;
	}
	else if (stick == 2)
	{
		return m_joystickValues[joy].second->y;
	}
	return 0;
}

//-------------------------------------------------------------------------------
//GETTERS
//-------------------------------------------------------------------------------

//Get Key Up
char TheInput::GetKeyUp() const
{
	return m_keyUp;
}

//Get Key Down
char TheInput::GetKeyDown() const
{

	return m_keyDown;

}

//Get is X clicked
bool TheInput::GetIsXClicked() const
{
	return m_isXClicked;
}

//Get joysticks initialized
bool TheInput::GetJoysticksInitialized() const
{
	return m_areJoysticksInitialised;
}

//Get Mouse motion on X
int TheInput::GetMouseMotionX() const
{
	return m_mouseMotionX;
}

//Get Mouse Motion on Y
int TheInput::GetMouseMotionY() const
{
	return m_mouseMotionY;
}

//Get Mouse x position
int TheInput::GetMousePositionX() const
{
	return m_mousePositionX;
}

//Get Mouse y position
int TheInput::GetMousePositionY() const
{
	return m_mousePositionY;
}

//Get is Controller Active
bool TheInput::GetIsControllerActive() const
{
	return m_isControllerActive;
}

//Get Key States
KeyState TheInput::GetKeyStates() const
{
	return m_keyStates;
}

//Get Motion
glm::vec2 TheInput::GetMotion() const
{
	return m_motion;
}

bool TheInput::GetDevMode() const
{
	return m_isDevMode;
}

void TheInput::SetDevMode(const bool& value)
{
	m_isDevMode = value;
}

//-------------------------------------------------------------------------------
//SETTERS
//-------------------------------------------------------------------------------

//Set X Motion
void TheInput::SetMotionX(const int& value)
{
	m_motion.x = value;
}

//Set Y Motion
void TheInput::SetMotionY(const int& value)
{
	m_motion.y = value;
}


