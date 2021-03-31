#pragma once
#ifdef _PTSDINPUT
#define INPUTAPI  __declspec(dllexport)   // export DLL information

#else
#define INPUTAPI  __declspec(dllimport)   // import DLL information

#endif 

#include "PTSDkeys.h"
#include "Vec2.h"

namespace PTSD {
	class InputImp;

	class INPUTAPI Input {
	private:

	public:
		static int Init();

		~Input() {}
		Input() {}

		size_t createInput();

		int Shutdown();

		static void test();

		static bool keyPressed(Scancode key);

		bool mouseLeftClick();

		bool mouseRightClick();

		bool mouseWheelClick();

		Vector2D getMousePos();

		bool keyReleased(Scancode key);

		bool ControllerButtonPressed(int controllerID, ControllerButton button);

		bool ControllerButtonReleased(int controllerID, ControllerButton button);

		Vector2D controllerRightAxis(int controllerID);

		Vector2D controllerLeftAxis(int controllerID);

		float controllerLeftTrigger(int controllerID);

		float controllerRightTrigger(int controllerID);

		void update();
	};
}