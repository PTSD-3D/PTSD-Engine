#include <iostream>
#include "LogManager.h"
#include "PhysicsManager.h"
#include "GraphicsManager.h"
#include "ScriptManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "Camera.h"
#include "UIManager.h"
#include "test.h"
#include <SDL_timer.h>
#include "Entity.h"
#include "Component.h"
#include "TransformComponent.h"

#ifndef NDEBUG
	#define _DEBUG 1
#endif // !-DNDEBUG


int main()
{
	PTSD::Log* logSystem = new PTSD::Log();

#ifdef _DEBUG
	logSystem->init(PTSD::Trace);
#else
	logSystem->init(PTSD::Warning);
#endif
	PTSD::LOG("Beginning Initialization");
	PTSD::GraphicsManager::init();
	PTSD::InputManager::init();
	PTSD::UIManager::init();
	PTSD::PhysicsManager::init();
	PTSD::SoundManager::init();
	PTSD::ScriptManager* scriptingSystem = new PTSD::ScriptManager();
	
	//Cache singletons
	PTSD::GraphicsManager* graphicsSystem = PTSD::GraphicsManager::getInstance();
	PTSD::InputManager* inputSystem = PTSD::InputManager::getInstance();
	PTSD::PhysicsManager* physicsSystem = PTSD::PhysicsManager::getInstance();
	PTSD::UIManager* uiSystem = PTSD::UIManager::getInstance();
	PTSD::SoundManager* soundSystem = PTSD::SoundManager::getInstance();
	
	//PTSD::test_Sound(soundSystem); //If you want to test this module, you need to go to test.h and also comment out everything there.
	scriptingSystem->init();
	// auto sinbad = scriptingSystem->createEntity(0);
	// sinbad->addComponent<PTSD::DebugComponent>();

	//PTSD::TransformComponent* transform = PTSD::test_Transform_Setup(sinbad); //To test this you also need test_Transform_Update in the loop

	PTSD::LOG("All subsystems initialized");
	PTSD::Camera* myCam = graphicsSystem->getCam();

	//Initial LUA scripts
	scriptingSystem->run("Client/CameraScript.lua");

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
		while (accumulator>= deltaTime) { //The loop is executed only if it's time to proccess another cycle
			inputSystem->update();

			physicsSystem->update(deltaTime);
			//scriptingSystem->run("client/CameraScript.lua");
			//graphicsSystem->getCam()->translate({ 0,0,1 }); //To be deleted
      
			soundSystem->update();
			scriptingSystem->update();

			inputSystem->clean();
			//PTSD::LOG("update cycle complete", PTSD::Warning);
			accumulator -= deltaTime;

			// PTSD::test_Transform_Update(transform);//To test this you also need test_Transform_Setup outside of the loop

			running = !inputSystem->keyPressed(Scancode::SCANCODE_ESCAPE);
		}
		graphicsSystem->renderFrame(); //The frame is rendered even if the game has not been updated (for faster machines)
		uiSystem->render();
	}
	return 0;
}