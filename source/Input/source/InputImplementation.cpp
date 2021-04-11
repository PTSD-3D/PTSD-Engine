#include "InputImplementation.h"
#include <fstream>
#include <iostream>

#include "PTSDGraphics.h"

namespace PTSD {
	using namespace std;
	InputImplementation* InputImplementation::mInstance = nullptr;

	InputImplementation::InputImplementation() {
		clearState();
		numControllers_ = 0;
		for (int i = 0; i < kbSize; i++) {
			kbState_.push_back(ButtonState::Up);
		}
	}

	InputImplementation::~InputImplementation() {
		for (std::pair<Vector2D*, Vector2D*> e : mJoystickValues) {
			delete e.first;
			delete e.second;
		}
		for (std::pair<double*, double*> e : mTriggerValues) {
			delete e.first;
			delete e.second;
		}
	}

	size_t InputImplementation::createInput() {

		InputImplementation();
		return 0;
	}

	void InputImplementation::Init() {
		cout << "Buenas Tardes" << endl;
	}

	void InputImplementation::update() {
		SDL_Event event;

		clearState();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				onKeyDown(event);
				break;
			case SDL_KEYUP:
				onKeyUp(event);
				break;
			case SDL_MOUSEMOTION:
				onMouseMotion(event);
				break;
			case SDL_MOUSEBUTTONDOWN:
				onMouseButtonChange(event, true);
				break;
			case SDL_MOUSEBUTTONUP:
				onMouseButtonChange(event, false);
				break;
			case SDL_JOYAXISMOTION:
				onJoyAxisChange(event);
				break;
			case SDL_JOYBUTTONDOWN:
				onJoyButtonChange(event, JustDown);
				break;
			case SDL_JOYBUTTONUP:
				onJoyButtonChange(event, JustUp);
				break;
			case SDL_CONTROLLERDEVICEADDED:
				onControllerAddedEvent(event);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				onControllerRemovedEvent(event);
				break;
			case SDL_QUIT:
				//SDL_Game::instance()->exitGame();
				break;
			}
		}
	}

	void InputImplementation::clearState() {
		isKeyDownEvent_ = false;
		isKeyUpEvent_ = false;
		isMouseButtonEvent_ = false;
		isMouseMotionEvent_ = false;
		isAxisMovementEvent_ = false;
		isButtonDownEvent_ = false;
		isButtonUpEvent_ = false;

		//Adjust just pressed and released buttons
		for (int i = 0; i < 3; i++) {
			switch (mbState_[i])
			{
			case JustUp:
				mbState_[i] = Up;
				break;
			case JustDown:
				mbState_[i] = Down;
				break;
			default:
				break;
			}
		}
		while (!justDownKeys.empty()) {
			kbState_[justDownKeys.front()] = ButtonState::Down;
			justDownKeys.pop();
		}
		while (!justUpKeys.empty()) {
			kbState_[justUpKeys.front()] = ButtonState::Up;
			justUpKeys.pop();
		}

		for (int controller = 0; controller < mGameControllers.size(); controller++) {
			for (int j = 0; j < SDL_CONTROLLER_BUTTON_MAX; j++) {
				switch (mButtonStates[controller][j])
				{
				case(JustDown):
					mButtonStates[controller][j] = Down;
					break;
				case(JustUp):
					mButtonStates[controller][j] = Up;
					break;
				default:
					break;
				}
			}
		}
	}

	
	//Controllers
	void InputImplementation::clearJoysticks()
	{
		if (mBJoysticksInitialised)
		{
			for (auto& ctrl : mGameControllers) {
				SDL_GameControllerClose(ctrl);
			}
		}
	}

	void InputImplementation::onJoyAxisChange(SDL_Event& event) {
		isAxisMovementEvent_ = true;
		int whichOne = event.jaxis.which;
		const double normalize = 1.0 / 32768.0;
		double val = event.jaxis.value;
		// left stick move left or right

		Uint8 i = 0;
		bool bindFound = false;
		int bindedAxis;
		//hay que buscar el botón al que se corresponde
		//porque SDL es una librería maravillosa y super intuitiva
		while (!bindFound && i < SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_MAX) {
			SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForAxis(mGameControllers[whichOne], (SDL_GameControllerAxis)i);
			if (b.value.axis == event.jaxis.axis) {
				bindedAxis = i;
				bindFound = true;
			}
			i++;
		}
		//left stick right or left
		if (bindedAxis == 0)
		{
			if (val > mJoystickDeadZone)
			{
				mJoystickValues[whichOne].first->setX(val * normalize);
				lastLStickValue_[whichOne].x = (float)mJoystickValues[whichOne].first->getX();
			}
			else if (event.jaxis.value < -mJoystickDeadZone)
			{
				mJoystickValues[whichOne].first->setX(val * normalize);
				lastLStickValue_[whichOne].x = (float)mJoystickValues[whichOne].first->getX();
			}
			else
			{
				mJoystickValues[whichOne].first->setX(0);
			}
		}
		// left stick move up or down
		if (bindedAxis == 1)
		{
			if (event.jaxis.value > mJoystickDeadZone)
			{
				mJoystickValues[whichOne].first->setY(val * normalize);
				lastLStickValue_[whichOne].y = (float)mJoystickValues[whichOne].first->getY();
			}
			else if (event.jaxis.value < -mJoystickDeadZone)
			{
				mJoystickValues[whichOne].first->setY(val * normalize);
				lastLStickValue_[whichOne].y = (float)mJoystickValues[whichOne].first->getY();
			}
			else
			{
				mJoystickValues[whichOne].first->setY(0);
			}
		}
		//left trigger move up or down
		if (bindedAxis == 4) {
			if (event.jaxis.value > mTriggerDeadZone)
			{
				*mTriggerValues[whichOne].first = abs(event.jaxis.value);
			}
			else
			{
				*mTriggerValues[whichOne].first = 0;
			}
		}
		// right stick move left or right
		if (bindedAxis == 2)
		{
			if (event.jaxis.value > mJoystickDeadZone)
			{
				mJoystickValues[whichOne].second->setX(val * normalize);
			}
			else if (event.jaxis.value < -mJoystickDeadZone)
			{
				mJoystickValues[whichOne].second->setX(val * normalize);
			}
			else
			{
				mJoystickValues[whichOne].second->setX(0);
			}
		}
		// right stick move up or down
		if (bindedAxis == 3)
		{
			if (event.jaxis.value > mJoystickDeadZone)
			{
				mJoystickValues[whichOne].second->setY(val * normalize);
			}
			else if (event.jaxis.value < -mJoystickDeadZone)
			{
				mJoystickValues[whichOne].second->setY(val * normalize);
			}
			else
			{
				mJoystickValues[whichOne].second->setY(0);
			}
		}
		//right trigger move up or down
		if (bindedAxis == 5) {
			if (event.jaxis.value > mTriggerDeadZone)
			{
				*mTriggerValues[whichOne].second = abs(event.jaxis.value);
			}
			else
			{
				*mTriggerValues[whichOne].second = 0;
			}
		}

		float lastLx = mJoystickValues[whichOne].first->getX(), lastLy = mJoystickValues[whichOne].first->getY();

		if ((lastLx == 0 && lastLy >= 0.99) || (lastLx == 0 && lastLy <= -0.99) ||
			(lastLx >= 0.99 && lastLy == 0) || (lastLx <= -0.99 && lastLy == 0)) {
			lastLStickValue_[whichOne].x = lastLx;
			lastLStickValue_[whichOne].y = lastLy;
		}
	}

	void InputImplementation::onJoyButtonChange(SDL_Event& event, ButtonState just) {
		if (just == JustDown)
			isButtonDownEvent_ = true;
		else
			isButtonUpEvent_ = true;

		int whichOne = event.jaxis.which;
	//	cout << "Button down on SYSTEM " << whichOne << endl;

		Uint8 i = 0;
		bool bindFound = false;
		int bindedButton;
		//hay que buscar el botón al que se corresponde
		//porque SDL es una librería maravillosa y super intuitiva
		while (!bindFound && i < SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MAX) {
			SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForButton(mGameControllers[whichOne], (SDL_GameControllerButton)i);
			if (b.value.button == event.cbutton.button) {
				bindedButton = i;
				bindFound = true;
			}
			i++;
		}
		mButtonStates[whichOne][bindedButton] = just;
	}

	//bool InputHandler::mapJoystick(SDL_GameController* ctrl, json mapData) {
	//	const int bytes = 33;
	//	const int bits = bytes * 8;
	//	char guid[bits] = {};
	//	SDL_Joystick* joy = SDL_GameControllerGetJoystick(ctrl);
	//	SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(joy), guid, bits);
	//
	//	if (!(mapData[guid]).is_null()) {
	//		string mapString = mapData[guid];
	//		int res = SDL_GameControllerAddMapping(mapString.c_str());
	//
	//		return res == 1;
	//	}
	//	else {
	//		return false;
	//	}
	//	return false;
	//}

	void InputImplementation::onControllerAddedEvent(const SDL_Event& event)
	{
		if (numControllers_ < 4)
		{
			int idOnExit = mGameControllers.size();//su id fisica sera el lugar en el que lo inicialice SDL
			int gameId; //Su id del juego sera el id que lea de la id fisica
			if (disconnectedGameControllers_.empty()) {
				initialiseNewController(event.cdevice.which);

				//si es un mando nuevo, se corresponden
				gameId = idOnExit;
			}
			else {
				debugFlag_ReconectedController = true;
				int id = disconnectedGameControllers_.front();
				initialiseNewController(event.cdevice.which);
				disconnectedGameControllers_.pop();

				//si es un mando reconectado, el mando de sistema que habia perdido su input fisico leera del nuevo mando fisico
				gameId = id;
			}
			numControllers_++;
			systemToGameCtrlId.emplace(idOnExit, gameId);
			gameToSystemCtrlId[gameId] = idOnExit;
		}
	}

	void InputImplementation::onControllerRemovedEvent(const SDL_Event& event)
	{
		numControllers_--;
		int gameId;
		auto it = systemToGameCtrlId.find(event.cdevice.which);
		if (it != systemToGameCtrlId.end()) {
			disconnectedGameControllers_.push(it->second);
			systemToGameCtrlId.erase(it);
		}
		else {
			//se ha desconectado un mando no inicializado
			//eso es malo.
		}
	}

	void InputImplementation::initialiseNewController(int idOnEnter)
	{
		SDL_GameController* gameCtrl = SDL_GameControllerOpen(idOnEnter);
		if (gameCtrl)
		{
			//cout << "--------------" << endl;
			//cout << SDL_GameControllerName(gameCtrl) << endl;
			//cout << SDL_GameControllerMapping(gameCtrl) << endl;
			mGameControllers.push_back(gameCtrl);
			mJoystickValues.push_back(std::make_pair(
				new Vector2D(0, 0), new Vector2D(0, 0))); // add our pair
			mTriggerValues.push_back(std::make_pair
			(new double(0.0), new double(0.0)));

			lastLStickValue_.push_back(Vector2D(0, 0));

			std::vector<ButtonState> tempButtons;
			for (int j = 0; j < SDL_CONTROLLER_BUTTON_MAX; j++)
			{
				tempButtons.push_back(Up);
			}
			mButtonStates.push_back(tempButtons);
		}
		else
		{
			std::cout << SDL_GetError();
		}
		SDL_JoystickEventState(SDL_ENABLE);
		mBJoysticksInitialised = true;

		//std::cout << "Initialised " << m_gameControllers.size() << " joystick(s)";
	}

	void InputImplementation::setMousePosition(Vector2D pos)
	{
		SDL_WarpMouseInWindow(PTSD::Graphics::getInstance()->getSDLWindow(), pos.getX(), pos.getY());
	}

	void InputImplementation::initialiseGamepads() {
		/*if (-1 == SDL_GameControllerAddMappingsFromFile("./config/gamecontrollerdb.txt"))
			cout << "Error al cargar la base de datos" << endl;*/
		if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
			SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		}
		numControllers_ = SDL_NumJoysticks();
	}

	bool InputImplementation::isButtonJustUp(int gameCtrl, SDL_GameControllerButton b)
	{
		int ctrl = gameToSystemCtrlId[gameCtrl];
		if (ctrl >= mGameControllers.size())
			return false;
		return(isButtonUpEvent_ && mButtonStates[ctrl][b] == JustUp);
	}

	bool InputImplementation::isButtonJustDown(int gameCtrl, SDL_GameControllerButton b)
	{
		int ctrl = gameToSystemCtrlId[gameCtrl];
		if (ctrl >= mGameControllers.size())
			return false;
		return(isButtonDownEvent_ && mButtonStates[ctrl][b] == JustDown);
	}

	bool InputImplementation::isButtonDown(int gameCtrl, SDL_GameControllerButton b)
	{
		int ctrl = gameToSystemCtrlId[gameCtrl];

		if (ctrl >= mGameControllers.size())
			return false;
		return(mButtonStates[ctrl][b] == Down);
	}

	bool InputImplementation::isButtonUp(int gameCtrl, SDL_GameControllerButton b)
	{
		int ctrl = gameToSystemCtrlId[gameCtrl];
		if (ctrl >= mGameControllers.size())
			return false;
		return(mButtonStates[ctrl][b] == Up);
	}

	Vector2D InputImplementation::getStickDir(int gameCtrl, GAMEPADSTICK stick) {
		int ctrl = gameToSystemCtrlId[gameCtrl];
		if (ctrl >= mGameControllers.size())
			return Vector2D(0, 0);
		Vector2D aux;
		if (stick == LEFTSTICK)
			aux = *mJoystickValues[ctrl].first;
		else
			aux = *mJoystickValues[ctrl].second;

		aux = aux.normalize();
		return Vector2D{ aux.getX(), aux.getY() };
	}

	Vector2D InputImplementation::getLastStickDir(int gameCtrl, GAMEPADSTICK stick) {
		int ctrl = gameToSystemCtrlId[gameCtrl];
		if (ctrl >= mGameControllers.size())
			return Vector2D(0, 0);
		if (stick == LEFTSTICK)
			return lastLStickValue_[ctrl];
		else
			return Vector2D{ 0, 0 };
	}

	double InputImplementation::getStickX(int gameJoy, GAMEPADSTICK stick)
	{
		int joy = gameToSystemCtrlId[gameJoy];
		if (joy >= mGameControllers.size())
			return 0.0;
		if (mJoystickValues.size() > 0)
		{
			if (stick == LEFTSTICK)

			{
				return mJoystickValues[joy].first->getX();
			}
			else if (stick == RIGHTSTICK)
			{
				return mJoystickValues[joy].second->getX();
			}
		}
		return 0;
	}

	double InputImplementation::getStickY(int gameJoy, GAMEPADSTICK stick)
	{
		int joy = gameToSystemCtrlId[gameJoy];
		if (joy >= mGameControllers.size())
			return 0.0;
		if (mJoystickValues.size() > joy)
		{
			if (stick == LEFTSTICK)
			{
				return mJoystickValues[joy].first->getY();
			}
			else if (stick == RIGHTSTICK)
			{
				return mJoystickValues[joy].second->getY();
			}
		}
		return 0;
	}

	double InputImplementation::getTrigger(int gameJoy, GAMEPADTRIGGER trigger) {
		int joy = gameToSystemCtrlId[gameJoy];
		if (mJoystickValues.size() > joy)
		{
			if (trigger == LEFTTRIGGER)
			{
				return *mTriggerValues[joy].first;
			}
			else if (trigger == RIGHTTRIGGER)
			{
				return *mTriggerValues[joy].second;
			}
		}
		return 0;
	}

}