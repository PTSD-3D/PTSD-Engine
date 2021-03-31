#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDSound.h"
#include "PTSDUI.h"
#include "PTSDInput.h"
#include "Camera.h"
#include "Vec3.h"

int main()
{
	PTSD::Input* inputSystem = new PTSD::Input();
	PTSD::Log* logSystem = new PTSD::Log();
	PTSD::Graphics* graphicsSystem = PTSD::Graphics::getInstance();
	PTSD::Scripting* scriptingSystem = new PTSD::Scripting();
	PTSD::PTSDPhysics* physicsSystem = new PTSD::PTSDPhysics();
	PTSD::UI* uiSystem = new PTSD::UI();
	PTSD::PTSDSound* soundSystem = new PTSD::PTSDSound();

#ifdef _DEBUG
	logSystem->Init(PTSD::Trace);
#else
	logSystem->Init(PTSD::Warning);
#endif
	PTSD::LOG("Beginning Initialization");
	soundSystem->Init();
	inputSystem->Init();
	physicsSystem->Init();
	graphicsSystem->init();
	uiSystem->Init();
	scriptingSystem->init();
	PTSD::LOG("All subsystems initialized");

	PTSD::Camera* myCam = graphicsSystem->getCam();
	while(true)
	{
		graphicsSystem->renderFrame();
		graphicsSystem->getCam()->translate({ 0,0,0.1 });
	}
}
