#include "PTSDInput.h"
#include "InputImp.h"

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

#include <iostream>

namespace PTSD {

	int Input::Init() {

		SDL_Init(SDL_INIT_EVERYTHING);

		if (!SDL_WasInit(SDL_INIT_VIDEO))
			SDL_InitSubSystem(SDL_INIT_VIDEO);

		//Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI; //SDL_WINDOW_RESIZABLE

		//SDL_Window* sdlWindow = SDL_CreateWindow("HOLI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 300, flags);

		//SDL_SysWMinfo wmInfo;
		//SDL_VERSION(&wmInfo.version);

		////Additional configuration
		//SDL_SetWindowGrab(sdlWindow, SDL_bool(false));
		//SDL_ShowCursor(false);

		//SDL_Event e;

		bool salir = false;

		////Input singleton
		InputImp* aux = nullptr;
		aux = InputImp::getInstance();
		aux->createInput();
		aux->initialiseGamepads();


		//while (!salir) {

		//	test(aux);
		//	aux->update();
		//	salir = keyPressed(); /*(aux->isKeyDown(SDL_SCANCODE_LEFT))*/
		//}

		return 0;
	}

	size_t Input::createInput()
	{
		return InputImp::getInstance()->createInput();
	}

	int Input::Shutdown()
	{
		delete InputImp::getInstance();
		return 0;
	}

	void Input::update() {
		InputImp::getInstance()->update();
	}

	void Input::test() {
		InputImp* aux = InputImp::getInstance();
		/*Vector2D pos = aux->getMousePos();
		cout << pos.x << " " << pos.y << endl;*/

		/*if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_A)) cout << "a" << endl;
		if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_B)) cout << "b" << endl;
		if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_X)) cout << "x" << endl;
		if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_Y)) cout << "y" << endl;
		if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_BACK)) cout << "back" << endl; 
		if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_START)) cout << "star" << endl; 
		if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) cout << "RB" << endl;
		if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) cout << "LB" << endl;
		if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_RIGHTSTICK)) cout << "right_stick" << endl;
		if (aux->isButtonDown(0, SDL_CONTROLLER_BUTTON_LEFTSTICK)) cout << "left_stick" << endl;*/

		/*Vector2D pos = aux->getStickDir(0, GAMEPADSTICK::RIGHTSTICK);
		cout << pos.x << " " << pos.y << endl;*/

		//cout << aux->getTrigger(0, GAMEPADTRIGGER::RIGHTTRIGGER) << endl;

//---------------------------------------------------------------------------

		if(keyPressed(SCANCODE_A))cout << "Tecla a pulsada" << endl;
		//if(keyRelease(SCANCODE_A))cout << "Tecla sin pulsar" << endl;
		 
		if (mouseLeftClick()) cout << "Click Izquierdo" << endl;
		if (mouseRightClick()) cout << "Click Derecho" << endl;
		if (mouseWheelClick()) cout << "Click Rueda del raton" << endl;

		if(ControllerButtonPressed(0, CONTROLLER_BUTTON_A)) cout << "Boton A pulsado" << endl;
		if(ControllerButtonReleased(0, CONTROLLER_BUTTON_A)) cout << "Boton A soltado" << endl;

		//Vector2D posY = controllerRightAxis(0);
		//cout << "RightAxis =" << posY.x << " " << posY.y << endl;

		//Vector2D posX = controllerLeftAxis(0);
		//cout << "LeftAxis =" << posX.x << " " << posX.y << endl;

		//cout << "Left Trigger =" << controllerLeftTrigger(0) << endl;
		//cout << "Right Trigger =" << controllerRightTrigger(0) << endl;
		
	}
	//Keyboard

	bool Input::keyPressed(Scancode key) {
		return InputImp::getInstance()->isKeyDown(static_cast<SDL_Scancode>(key));
	}

	bool Input::keyRelease(Scancode key) {
		return InputImp::getInstance()->isKeyUp(static_cast<SDL_Scancode>(key));
	}

	//Mouse

	bool Input::mouseLeftClick() {
		return InputImp::getInstance()->isMouseButtonDown(MOUSEBUTTON::LEFT);
	}

	bool Input::mouseRightClick() {
		return InputImp::getInstance()->isMouseButtonDown(MOUSEBUTTON::RIGHT);
	}

	bool Input::mouseWheelClick() {
		return InputImp::getInstance()->isMouseButtonDown(MOUSEBUTTON::MIDDLE);
	}

	Vector2D Input::getMousePos() {
		return InputImp::getInstance()->getMousePos();
	}
	//Controller

	bool Input::ControllerButtonPressed(int controllerID, ControllerButton button) {
		return InputImp::getInstance()->isButtonDown(controllerID, static_cast<SDL_GameControllerButton>(button)); 
	}

	bool Input::ControllerButtonReleased(int controllerID, ControllerButton button) {
		return InputImp::getInstance()->isButtonJustUp(controllerID, static_cast<SDL_GameControllerButton>(button));
	}

	Vector2D Input::controllerRightAxis(int controllerID) {
		return InputImp::getInstance()->getStickDir(controllerID, GAMEPADSTICK::RIGHTSTICK);
	}

	Vector2D Input::controllerLeftAxis(int controllerID) {
		return InputImp::getInstance()->getStickDir(controllerID, GAMEPADSTICK::LEFTSTICK);
	}

	float Input::controllerLeftTrigger(int controllerID) {
		return InputImp::getInstance()->getTrigger(controllerID, GAMEPADTRIGGER::LEFTTRIGGER);
	}

	float Input::controllerRightTrigger(int controllerID) {
		return InputImp::getInstance()->getTrigger(controllerID, GAMEPADTRIGGER::RIGHTTRIGGER);
	}
}