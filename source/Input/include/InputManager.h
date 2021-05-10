#pragma once

#include "PTSDAssert.h"
#include "PTSDkeys.h"
#include "PTSDVectors.h"

namespace PTSD {
	class InputImplementation;

	class InputManager {
	private:
		static InputManager* mInstance;
		InputImplementation* mImplementation = nullptr;
	public:

		InputManager() {}
		~InputManager() {}

		static InputManager* getInstance()
		{
			PTSD_ASSERT(mInstance != nullptr, "InputManager accessed before init");
			return mInstance;
		}

		static int init();
		size_t createInput();
		int Shutdown();
		void test();

	//Keyboard
		bool keyPressed(Scancode key);
		bool keyRelease(Scancode key);
		bool keyJustDown(Scancode key);
		bool keyJustUp(Scancode key);
		
	//Mouse
		bool isMouseButtonDown(MouseButton button);
		bool isMouseButtonJustDown(MouseButton button);
		bool isMouseButtonJustUp(MouseButton button);
		bool mouseMotion();
		Vector2D getMousePosition() const;
		Vector2D getMouseRelativePosition() const;

	//Controller
		bool ControllerButtonPressed(int controllerID, ControllerButton button);
		bool ControllerButtonReleased(int controllerID, ControllerButton button);
		bool ControllerButtonJustPressed(int controllerID, ControllerButton button);
		Vector2D controllerRightAxis(int controllerID);
		Vector2D controllerLeftAxis(int controllerID);
		float controllerLeftTrigger(int controllerID);
		float controllerRightTrigger(int controllerID);
		void update();
		void clean();
		void cleanMouseDelta();
	};
}