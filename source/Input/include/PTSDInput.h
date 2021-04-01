#pragma once

#include "PTSDkeys.h"
#include "PTSDVectors.h"

namespace PTSD {
	class InputImplementation;

	class Input {
	private:
		InputImplementation* mImplementation = nullptr;
	public:

		Input() {}
		~Input() {}
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
		Vector2D getMousePos();

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