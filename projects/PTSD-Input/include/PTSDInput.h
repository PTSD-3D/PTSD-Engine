#pragma once
#if defined(_MSC_VER)
	#ifdef _PTSDINPUT
		#define INPUTAPI  __declspec(dllexport)   // export DLL information
	#else
		#define INPUTAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDINPUT
		#define INPUTAPI __attribute__((visibility("default")))
	#else
		#define INPUTAPI
	#endif 
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

	//Keyboard
		static bool keyPressed(Scancode key);

		static bool keyRelease(Scancode key);
		
	//Mouse
		static bool mouseLeftClick();

		static bool mouseRightClick();

		static bool mouseWheelClick();

		static Vector2D getMousePos();

	//Controller

		static bool ControllerButtonPressed(int controllerID, ControllerButton button);

		static bool ControllerButtonReleased(int controllerID, ControllerButton button);

		static Vector2D controllerRightAxis(int controllerID);

		static Vector2D controllerLeftAxis(int controllerID);

		static float controllerLeftTrigger(int controllerID);

		static float controllerRightTrigger(int controllerID);

		void update();
	};
}