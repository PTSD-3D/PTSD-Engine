#pragma once

#include "PTSDkeys.h"
#include "PTSDVectors.h"

namespace PTSD {
	class InputImplementation;

	class Input {
	private:
		static Input* mInstance;
		InputImplementation* mImplementation = nullptr;
	public:

		Input() {}
		~Input() {}

		static Input* getInstance()
		{
			if (mInstance == nullptr)
				mInstance = new Input();
			return mInstance;
		}

		int init();
		size_t createInput();
		int Shutdown();
		void test();

	//Keyboard
		bool keyPressed(Scancode key);
		bool keyRelease(Scancode key);
		
	//Mouse
		bool mouseLeftClick();
		bool mouseRightClick();
		bool mouseWheelClick();
		bool mouseMotion();
		void setMousePosition(Vector2D pos);
		Vector2D getMousePos();
		float getMousePosX();
		float getMousePosY();

		void setMouseLock(bool b);

	//Controller
		bool ControllerButtonPressed(int controllerID, ControllerButton button);
		bool ControllerButtonReleased(int controllerID, ControllerButton button);
		Vector2D controllerRightAxis(int controllerID);
		Vector2D controllerLeftAxis(int controllerID);
		float controllerLeftTrigger(int controllerID);
		float controllerRightTrigger(int controllerID);
		void update();
	};
}