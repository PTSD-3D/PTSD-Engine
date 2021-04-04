#include <iostream>
#include "PTSDLog.h"
#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDSound.h"
#include "Sound.h"
#include "PTSDInput.h"
#include "Camera.h"
#include "PTSDUI.h"
#include "test.h"
#include <Windows.h> //Please delete me or Ricardo will kill me.

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
	soundSystem->Init();
	//PTSD::test_Sound(soundSystem); //If you want to test this module, you need to go to test.h and also comment out everything there.
	scriptingSystem->init();
	PTSD::LOG("All subsystems initialized");
	PTSD::Camera* myCam = graphicsSystem->getCam();
	while(true)
	{
		inputSystem->update();
		physicsSystem->update();
		graphicsSystem->getCam()->translate({ 0,0,0.1 });
		graphicsSystem->renderFrame();
		uiSystem->render();
	}

	return 0;
}