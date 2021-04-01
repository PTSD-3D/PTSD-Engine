#include <iostream>
#include "PTSDLog.h"
//#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
//#include "PTSDSound.h"
//#include "PTSDUI.h"
#include "PTSDInput.h"
#include "Camera.h"
//#include "Vec3.h"
//#include "Vec2.h"
//#include "PTSDkeys.h"

int main()
{
	PTSD::Log* logSystem = new PTSD::Log();
	PTSD::Input* inputSystem = new PTSD::Input();
	PTSD::Graphics* graphicsSystem = PTSD::Graphics::getInstance();
	PTSD::Scripting* scriptingSystem = new PTSD::Scripting();
	/*PTSD::PTSDPhysics* physicsSystem = new PTSD::PTSDPhysics();
	PTSD::UI* uiSystem = new PTSD::UI();
	PTSD::PTSDSound* soundSystem = new PTSD::PTSDSound();*/

#ifdef _DEBUG
	logSystem->init(PTSD::Trace);
#else
	logSystem->init(PTSD::Warning);
#endif
	PTSD::LOG("Beginning Initialization");
	//soundSystem->init();
	inputSystem->init();
	//physicsSystem->init();*/
	graphicsSystem->init();
	//uiSystem->init();
	scriptingSystem->init();
	PTSD::LOG("All subsystems initialized");

	PTSD::Camera* myCam = graphicsSystem->getCam();
	while(true)
	{
		inputSystem->update();
		graphicsSystem->getCam()->translate({ 0,0,0.1 });
		graphicsSystem->renderFrame();
		inputSystem->test();

	}
}
