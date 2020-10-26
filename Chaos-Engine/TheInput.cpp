#include "TheInput.h"
#include "Game.h"
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
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
	isControllerActive = false;

	initialiseJoysticks();

	areJoysticksDown = false;

	isEditorMode = true;
}

//-------------------------------------------------------------------------------
//Update Input manager, so keystates are recognized
//-------------------------------------------------------------------------------
void TheInput::Update()
{
	int SDL_ShowCursor(0);

	SDL_Event events;

	keyDown = 0;

	mouseMotionX = 0;
	mouseMotionY = 0;

	//Get the array of keys
	keyStates = SDL_GetKeyboardState(nullptr);

	//----------------------------------------------------------
	//Update Input manager, so keystates are recognized
	//----------------------------------------------------------

	while (SDL_PollEvent(&events))
	{
		//Imgui Events
		ImGui_ImplSDL2_ProcessEvent(&events);

		//If there's input events
		switch (events.type)
		{
			case SDL_QUIT:
			{
				isXClicked = true;
				Game::Instance()->ExitGame();

				break;
			}
			case SDL_KEYDOWN:
			{
				isControllerActive = false;

				keyDown = events.key.keysym.sym;
				isKeyDown = true;

				//Check if back space key is pressed, if yes delete char in the back from the vector
				if (events.key.keysym.sym = SDLK_BACKSPACE && keyboardInput.size() > 0)
				{
					keyboardInput.pop_back();
				}

				//Check if the key pressed is not an empty space, if yes add it to the vector
				else if (events.key.keysym.sym != SDLK_RETURN)
				{
					keyboardInput.push_back(keyDown);
				}

				break;
			}
			case SDL_KEYUP:
			{
				isControllerActive = false;

				keyUp = events.key.keysym.sym;
				isKeyDown = false;

				break;
			}
			case SDL_MOUSEMOTION:
			{
				isControllerActive = false;

				mouseMotionX = events.motion.xrel;
				mouseMotionY = events.motion.yrel;

				mousePositionX = events.motion.x;
				mousePositionY = events.motion.y;

				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						isLeftButtonDown = true;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						isRightButtonDown = true;
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						isMiddleButtonDown = true;
						break;
					}
				}

				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						isLeftButtonDown = false;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						isRightButtonDown = false;
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						isMiddleButtonDown = false;
						break;
					}
				}

				break;
			}
			case SDL_JOYAXISMOTION:
			{
				//Get which controller
				int whichOne = events.jaxis.which;

				//Left stick move left or right
				if (events.jaxis.axis == 0)
				{
					isControllerActive = true;

					if (events.jaxis.value > JOYSTICKDEADZONE)
					{
						joystickValues[whichOne].first->x = 1;
					}
					else if (events.jaxis.value < -JOYSTICKDEADZONE)
					{
						joystickValues[whichOne].first->x = -1;
					}
					else
					{
						joystickValues[whichOne].first->x = 0;
					}
				}

				//Left stick move up or down
				if (events.jaxis.axis == 1)
				{
					isControllerActive = true;

					if (events.jaxis.value > JOYSTICKDEADZONE)
					{
						joystickValues[whichOne].first->y = 1;
					}
					else if (events.jaxis.value < -JOYSTICKDEADZONE)
					{
						joystickValues[whichOne].first->y = -1;
					}
					else
					{
						joystickValues[whichOne].first->y = 0;
					}
				}

				//Right stick move left or right
				if (events.jaxis.axis == 3)
				{
					isControllerActive = true;

					if (events.jaxis.value > JOYSTICKDEADZONE)
					{
						events.jaxis.value = 0;
						joystickValues[whichOne].second->x = 1;
					}
					else if (events.jaxis.value < -JOYSTICKDEADZONE)
					{
						events.jaxis.value = 0;
						joystickValues[whichOne].second->x = -1;
					}
					else
					{
						events.jaxis.value = 0;
						joystickValues[whichOne].second->x = 0;
					}
				}

				//Right stick move up or down
				if (events.jaxis.axis == 4)
				{

					isControllerActive = true;

					if (events.jaxis.value > JOYSTICKDEADZONE)
					{
						events.jaxis.value = 0;
						joystickValues[whichOne].second->y = 1;
					}
					else if (events.jaxis.value < -JOYSTICKDEADZONE)
					{
						events.jaxis.value = 0;
						joystickValues[whichOne].second->y = -1;
					}
					else
					{
						events.jaxis.value = 0;
						joystickValues[whichOne].second->y = 0;
					}
				}

				break;
			}
			case SDL_JOYBUTTONDOWN:
			{
				isControllerActive = true;		
			}
			case SDL_JOYHATMOTION:
			{
				isControllerActive = true;
				hatDown = events.jhat.hat;
			}
		}	
	}
}

//-------------------------------------------------------------------------------
//Initialise Joysticks
//-------------------------------------------------------------------------------
void TheInput::initialiseJoysticks()
{
	//Check if joystick substystem has been initialised
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	//Check if there are joysticks available
	if (SDL_NumJoysticks > 0)
	{
		//Loop through joysticks, open them and add them to vector
		for (size_t i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			joysticks.push_back(joy);

			joystickValues.push_back(std::make_pair(new glm::vec2(0, 0), new glm::vec2(0, 0)));
		}

		//Start listening for Joystick events
		SDL_JoystickEventState(SDL_ENABLE);

		//Set joysticks flag to true and output amount of joysticks
		if (joysticks.size() > 0)
		{
			areJoysticksInitialised = true;
		}
		else
		{
			areJoysticksInitialised = false;
		}

		std::cout << "Initialised: " << joysticks.size() << " Joystick(s)" << std::endl;
	}
	else
	{
		areJoysticksInitialised = false;
	}
}

//-------------------------------------------------------------------------------
//Clean Function(close Joysticks)
//-------------------------------------------------------------------------------
void TheInput::Destroy()
{
	//check if joysticks are initialised
	if (areJoysticksInitialised)
	{
		//Loop through joysticks and close them
		for (size_t i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(joysticks[i]);
		}
	}
}

//-------------------------------------------------------------------------------
//Get Joystick x value
//-------------------------------------------------------------------------------
int TheInput::GetJoystickXValue(const int& joy, const int& stick)
{
	if (joystickValues.size() > 0)
	{	
		if (stick == 1)
		{
			return joystickValues[joy].first->x;
		}
		else if (stick == 2)
		{
			return joystickValues[joy].second->x;
		}
	}

	return 0;
}

//-------------------------------------------------------------------------------
//Get Joystick y value
//-------------------------------------------------------------------------------
int TheInput::GetJoystickYValue(const int& joy, const int& stick)
{
	if (stick == 1)
	{
		return joystickValues[joy].first->y;
	}
	else if (stick == 2)
	{
		return joystickValues[joy].second->y;
	}
	return 0;
}

//-------------------------------------------------------------------------------
//GETTERS
//-------------------------------------------------------------------------------

//Get Key Up
char TheInput::GetKeyUp() const
{
	return keyUp;
}

//Get Key Down
char TheInput::GetKeyDown() const
{

	return keyDown;

}

//Get is X clicked
bool TheInput::GetIsXClicked() const
{
	return isXClicked;
}

//Get joysticks initialized
bool TheInput::GetJoysticksInitialized() const
{
	return areJoysticksInitialised;
}

//Get Mouse motion on X
int TheInput::GetMouseMotionX() const
{
	return mouseMotionX;
}

//Get Mouse Motion on Y
int TheInput::GetMouseMotionY() const
{
	return mouseMotionY;
}

//Get Mouse x position
int TheInput::GetMousePositionX() const
{
	return mousePositionX;
}

//Get Mouse y position
int TheInput::GetMousePositionY() const
{
	return mousePositionY;
}

//Get is Controller Active
bool TheInput::GetIsControllerActive() const
{
	return isControllerActive;
}

//Get Key States
KeyState TheInput::GetKeyStates() const
{
	return keyStates;
}

//Get Motion
glm::vec2 TheInput::GetMotion() const
{
	return motion;
}

//Get Button Down
bool TheInput::GetMouseButtonDown(const int& mouseid) const
{
	switch (mouseid)
	{
	case 0:
	{
		if (isLeftButtonDown)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	case 1:
	{
		if (isRightButtonDown)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	case 2:
	{
		if (isLeftButtonDown)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	default:

		break;
	}
}

//Get Editor Mode
bool TheInput::GetEditorMode() const
{
	return isEditorMode;
}

//Set Editor Mode
void TheInput::SetEditorMode(const bool& value)
{
	isEditorMode = value;
}

//-------------------------------------------------------------------------------
//SETTERS
//-------------------------------------------------------------------------------

//Set X Motion
void TheInput::SetMotionX(const int& value)
{
	motion.x = value;
}

//Set Y Motion
void TheInput::SetMotionY(const int& value)
{
	motion.y = value;
}


