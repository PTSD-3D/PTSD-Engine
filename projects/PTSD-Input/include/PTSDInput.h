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
	class InputImplementation;

	class INPUTAPI Input {
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