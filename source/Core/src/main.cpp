#ifdef _WIN32
#include "Windows.h"
#endif

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

#ifdef _DEBUG
	int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(152776);
#else
#ifdef _WIN32
	int WINAPI
	WinMain(HINSTANCE zHInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
	int main(){
#endif
#endif
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

	if(!scriptingSystem->init())
	{
		PTSD::LOG("Could not initialize the Script Manager", PTSD::LogLevel::Critical, 0);
		return EXIT_FAILURE;
	}

	PTSD::LOG("All subsystems initialized");

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
			inputSystem->update(running);

			physicsSystem->update(deltaTime);
      
			soundSystem->update();
			uiSystem->update();
			scriptingSystem->update();

			inputSystem->clean();
			//PTSD::LOG("update cycle complete", PTSD::Warning);
			accumulator -= deltaTime;
			if (running)
				running = scriptingSystem->isRunning();
		}
		graphicsSystem->renderFrame(); //The frame is rendered even if the game has not been updated (for faster machines)
		uiSystem->render();
	}

	scriptingSystem->shutdown();
	delete scriptingSystem;
	soundSystem->shutdown();
	physicsSystem->shutdown();
	uiSystem->shutdown();
	inputSystem->Shutdown();
	graphicsSystem->shutdown();
	logSystem->shutdown();

	delete logSystem;

	return EXIT_SUCCESS;
}