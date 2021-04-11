#include <iostream>
#include "PTSDLog.h"
#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "ScriptManager.h"
#include "PTSDSound.h"
#include "Sound.h"
#include "PTSDInput.h"
#include "Camera.h"
#include "PTSDUI.h"
#include "test.h"
#include <SDL_timer.h>
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"

int main()
{
	PTSD::Log* logSystem = new PTSD::Log();
	PTSD::Graphics* graphicsSystem = PTSD::Graphics::getInstance();
	PTSD::Input* inputSystem = PTSD::Input::getInstance();
	PTSD::UI* uiSystem = new PTSD::UI();
	PTSD::Physics* physicsSystem = PTSD::Physics::getInstance();
	PTSD::PTSDSound* soundSystem = new PTSD::PTSDSound();
	PTSD::ScriptManager* scriptingSystem = new PTSD::ScriptManager();

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
	PTSD::Entity* sinbad = scriptingSystem->createEntity();
	sinbad->addComponent<PTSD::DebugComponent>();
	PTSD::LOG("All subsystems initialized");
	PTSD::Camera* myCam = graphicsSystem->getCam();

	//Initial LUA scripts
	scriptingSystem->run("CameraScript.lua");

	inputSystem->setMouseLock(true);


	//GAME LOOP (all times in miliseconds)
	bool running = true;
	const Uint32 deltaTime = 33; //33 miliseconds per frame, ~30fps
	Uint32 accumulator = 0;
	Uint32 currentTime = SDL_GetTicks();
	Uint32 newTime;
	while (running) {
		newTime = SDL_GetTicks();
		Uint32 frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime; //If we're lagging behind the game will be updated as many times as needed to catch up
		inputSystem->setMousePosition(Vector2D(0, 0));
		while (accumulator>= deltaTime) { //The loop is executed only if it's time to proccess another cycle
			inputSystem->update();
			physicsSystem->update();
			graphicsSystem->getCam()->translate({ 0,0,0.1 });
			soundSystem->update();
			scriptingSystem->update();
			//PTSD::LOG("update cycle complete", PTSD::Warning);
			accumulator -= deltaTime;

			running = !inputSystem->keyPressed(Scancode::SCANCODE_ESCAPE);
		}
		graphicsSystem->renderFrame(); //The frame is rendered even if the game has not been updated (for faster machines)
		uiSystem->render();
	}
	return 0;
}