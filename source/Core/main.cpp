#include <iostream>
#include "PTSDLog.h"
#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDSound.h"
#include "PTSDInput.h"
#include "PTSDUI.h"
#include "Camera.h"

int main()
{
	PTSD::Log* logSystem = new PTSD::Log();
	PTSD::Graphics* graphicsSystem = PTSD::Graphics::getInstance();
	PTSD::Input* inputSystem = new PTSD::Input();
	PTSD::UI* uiSystem = new PTSD::UI();
	PTSD::Physics* physicsSystem = PTSD::Physics::getInstance();
	PTSD::PTSDSound* soundSystem = new PTSD::PTSDSound();
	PTSD::Scripting* scriptingSystem = new PTSD::Scripting();

#ifdef _DEBUG
	logSystem->init(PTSD::Trace);
#else
	logSystem->init(PTSD::Warning);
#endif
	PTSD::LOG("Beginning Initialization");
	graphicsSystem->init();
	inputSystem->init();
	uiSystem->init();
	physicsSystem->init();
	soundSystem->init();
	scriptingSystem->init();
	PTSD::LOG("All subsystems initialized");

	PTSD::Camera* myCam = graphicsSystem->getCam();

	//GAME LOOP
	bool running = true;
	double deltaTime = 0.033;
	double accumulator = 0;
	double currentTime = 0;

	while (running) {
		double newTime; //= getTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= deltaTime) {
			inputSystem->update();
			physicsSystem->update();
			graphicsSystem->getCam()->translate({ 0,0,0.1 });
			scriptingSystem->update();
			//soundSystem->update();
			accumulator -= deltaTime;
		}
		graphicsSystem->renderFrame();
		uiSystem->render();
	}

	return 0;
}
