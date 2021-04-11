#pragma once
#include "PTSDInput.h"
#include <SDL.h>
#include <array>
#include <vector>
#include <memory>
//#include "checkML.h"
#include <iterator>
#include <queue>
#include <map>
#include <string>
#include "PTSDVectors.h"

namespace PTSD {
	using namespace std;

	//Enums for identification of buttons, triggers and states
	enum MOUSEBUTTON : Uint8 {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};
	enum GAMEPADSTICK : Uint8 {
		LEFTSTICK = 1, RIGHTSTICK = 2
	};
	enum GAMEPADTRIGGER : Uint8 {
		LEFTTRIGGER = 1, RIGHTTRIGGER = 2
	};
	enum ButtonState :Uint8 {
		Up = 0, JustUp, Down, JustDown
	};

	class InputImplementation {
	private:

		static InputImplementation* mInstance;
		InputImplementation();

		//Generic keyboard press
		bool isKeyUpEvent_;
		bool isKeyDownEvent_;

		//---------------------------------------------
		//Generic mouse motion
		bool isMouseMotionEvent_;
		bool isMouseButtonEvent_;
		Vector2D mousePos_;
		std::array<ButtonState, 3> mbState_;
		//---------------------------------------------

		//Variables for controller input
		int numControllers_;
		std::vector<SDL_GameController*> mGameControllers; //Pointers for SDL controllers
		std::queue<int> disconnectedGameControllers_;	//Queue for disconected controllers

		//State of the inputs from a controller
		std::vector<std::pair<Vector2D*, Vector2D*>> mJoystickValues;
		std::vector<std::pair<double*, double*>> mTriggerValues;
		std::vector<std::vector<ButtonState>> mButtonStates;
		std::vector<Vector2D> lastLStickValue_;

		
		//State of the inputs from a keyboard and mouse
		ButtonState mMouseButtonStates[3];
		std::vector<SDL_Scancode> mKeysJustDown; 
		std::vector<SDL_Scancode> mKeysJustUp; 
		const int kbSize = 300;
		std::vector<ButtonState> kbState_;
		std::queue<int> justUpKeys;
		std::queue<int> justDownKeys;

		//Reconexion of controllers
		int gameToSystemCtrlId[4] = { -1,-1,-1,-1 }; //Store ids of the different controllers
		std::map<int, int> systemToGameCtrlId;

		bool debugFlag_ReconectedController = false;

		bool mBJoysticksInitialised;
		bool isButtonDownEvent_;
		bool isButtonUpEvent_;
		bool isAxisMovementEvent_;

		//
		//Methods
		//
		//controllers
		void clearState();
		void clearJoysticks();

		inline void onJoyAxisChange(SDL_Event& event);
		inline void onJoyButtonChange(SDL_Event& event, ButtonState just);
		//inline bool mapJoystick(SDL_GameController* joy, json mapData);	//For input mapping from json
		inline void onControllerAddedEvent(const SDL_Event& event);
		inline void onControllerRemovedEvent(const SDL_Event& event);
		inline void initialiseNewController(int i);
		//---------------------------------------------

		//keyboard
		inline void onKeyDown(SDL_Event& event) {
			isKeyDownEvent_ = true;
			if (kbState_[event.key.keysym.scancode] == ButtonState::Up) {
				kbState_[event.key.keysym.scancode] = ButtonState::JustDown;
				justDownKeys.push(event.key.keysym.scancode);
			}
		}
		inline void onKeyUp(SDL_Event& event) {
			isKeyUpEvent_ = true;
			if (kbState_[event.key.keysym.scancode] == ButtonState::Down) {
				kbState_[event.key.keysym.scancode] = ButtonState::JustUp;
				justUpKeys.push(event.key.keysym.scancode);
			}
		}
		//---------------------------------------------
		//mouse
		inline void onMouseMotion(SDL_Event& event) {
			isMouseMotionEvent_ = true;
			mousePos_.x = event.motion.x;
			mousePos_.y = event.motion.y;
		}
		inline void onMouseButtonChange(SDL_Event& event, bool isDown) {
			isMouseButtonEvent_ = true;
			if (event.button.button == SDL_BUTTON_LEFT) {
				mbState_[LEFT] = (isDown) ? JustDown : JustUp;
			}
			else if (event.button.button == SDL_BUTTON_MIDDLE) {
				mbState_[MIDDLE] = (isDown) ? JustDown : JustUp;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				mbState_[RIGHT] = (isDown) ? JustDown : JustUp;
			}
		}
		//---------------------------------------------


	public:
		~InputImplementation();
		InputImplementation(InputImplementation&) = delete;
		InputImplementation& operator=(InputImplementation&) = delete;
		
		static InputImplementation* getInstance()
		{
			if (!mInstance)
				mInstance = new InputImplementation();
			return mInstance;
		}

		size_t createInput();

		void Init();
		void update();

		const int mJoystickDeadZone = 10000;
		const int mTriggerDeadZone = 10000; //trigger deadzone equals threshold

		//Methods to get the information about some kind of input
		//---------------------------------------------

		// keyboard
		inline bool keyDownEvent() {
			return isKeyDownEvent_;
		}
		inline bool keyUpEvent() {
			return isKeyUpEvent_;
		}
		inline bool isKeyDown(SDL_Scancode key) {
			// return kbState_[key] == 1;
			return kbState_[key] == ButtonState::Down;
		}
		inline bool isKeyDown(SDL_Keycode key) {
			return isKeyDown(SDL_GetScancodeFromKey(key));
		}
		inline bool isKeyUp(SDL_Scancode key) {
			// kbState_[key] == 0;
			return kbState_[key] == ButtonState::Up;
		}
		inline bool isKeyUp(SDL_Keycode key) {
			return isKeyUp(SDL_GetScancodeFromKey(key));
		}
		inline bool isKeyJustDown(SDL_Keycode key) {
			return kbState_[SDL_GetScancodeFromKey(key)] == ButtonState::JustDown;
		}
		inline bool isKeyJustUp(SDL_Keycode key) {
			return kbState_[SDL_GetScancodeFromKey(key)] == ButtonState::JustUp;
		}
		//---------------------------------------------

		// mouse
		inline bool mouseMotionEvent() {
			return isMouseMotionEvent_;
		}
		inline bool mouseButtonEvent() {
			return isMouseButtonEvent_;
		}
		Vector2D getMousePos() {
			return mousePos_;
		}
		float getMousePosX() {
			return mousePos_.getX();
		}
		float getMousePosY() {
			return mousePos_.getY();
		}

		void setMouseLock(bool b) {
			if (b) SDL_SetRelativeMouseMode(SDL_bool::SDL_TRUE);
			else SDL_SetRelativeMouseMode(SDL_bool::SDL_FALSE);
		}

		void setMousePosition(Vector2D pos);

		inline bool isMouseButtonUp(MOUSEBUTTON mb) {
			return mbState_[mb] == Up || mbState_[mb] == JustUp;
		}
		inline bool isMouseButtonDown(MOUSEBUTTON mb) {
			return mbState_[mb] == Down || mbState_[mb] == JustDown;
		}
		inline bool isMouseButtonJustDown(MOUSEBUTTON mb) {
			return mbState_[mb] == JustDown;
		}
		inline bool isMouseButtonJustUp(MOUSEBUTTON mb) {
			return mbState_[mb] == JustUp;
		}
		//---------------------------------------------

		// Joystick
		//init
		void initialiseGamepads();
		bool joysticksInitialised() {
			return mBJoysticksInitialised;
		}
		int getNumControllers() {
			return numControllers_;
		}

		//Ask for this variables when asking for input
		//type of events
		inline bool isButonDownEvent() {
			return isButtonDownEvent_;
		}
		inline bool isButtonUpEvent() {
			return isButtonUpEvent_;
		}
		inline bool isAxisMovementEvent() {
			return isAxisMovementEvent_;
		}

		//justup/down for the exact press or release
		bool isButtonJustUp(int gameCtrl, SDL_GameControllerButton b);
		bool isButtonJustDown(int gameCtrl, SDL_GameControllerButton b);

		//isup/down for holding a button
		bool isButtonDown(int gameCtrl, SDL_GameControllerButton b);
		bool isButtonUp(int gameCtrl, SDL_GameControllerButton b);

		//get the direction or a value from a stick/trigger given a controller
		Vector2D getStickDir(int ctrl, GAMEPADSTICK stick);
		Vector2D getLastStickDir(int ctrl, GAMEPADSTICK stick);
		double getStickX(int ctrl, GAMEPADSTICK stick);
		double getStickY(int ctrl, GAMEPADSTICK stick);
		double getTrigger(int ctrl, GAMEPADTRIGGER trigger);
	};
}