#include <iostream>
#include "PTSDLog.h"
//#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDSound.h"
#include "PTSDUI.h"
#include "PTSDInput.h"
#include "Camera.h"

int main()
{
	PTSD::Log* logSystem = new PTSD::Log();
	PTSD::Graphics* graphicsSystem = PTSD::Graphics::getInstance();
	PTSD::Input* inputSystem = new PTSD::Input();
	PTSD::Scripting* scriptingSystem = new PTSD::Scripting();
	//PTSD::Physics* physicsSystem = PTSD::Physics::getInstance();
	PTSD::UI* uiSystem = new PTSD::UI();
	PTSD::PTSDSound* soundSystem = new PTSD::PTSDSound();

#ifdef _DEBUG
	logSystem->init(PTSD::Trace);
#else
	logSystem->init(PTSD::Warning);
#endif
	PTSD::LOG("Beginning Initialization");
	graphicsSystem->init();
	inputSystem->init();
	//physicsSystem->init();
	uiSystem->init();
	soundSystem->init();
	scriptingSystem->init();
	PTSD::LOG("All subsystems initialized");

	PTSD::Camera* myCam = graphicsSystem->getCam();
	while(true)
	{
		inputSystem->update();
		//physicsSystem->update();
		graphicsSystem->getCam()->translate({ 0,0,0.1 });
		graphicsSystem->renderFrame();
		uiSystem->render();
	}
}
