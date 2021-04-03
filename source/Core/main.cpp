#include <iostream>
#include "PTSDLog.h"
#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDSound.h"
#include "Sound.h"
#include "PTSDInput.h"
#include "PTSDUI.h"
#include "Camera.h"
#include <Windows.h>

void test_Sound(PTSD::PTSDSound* m_soundSystem) {
	std::cout << "This is a sample test for the sound module. @test.cpp, test_Sound()\n If you don't want to test this again, please comment the call to this function in the main() function\n";
	m_soundSystem->playMusic("./assets/PTSD-Anthem.mp3", true);
	Sleep(500);
	m_soundSystem->setMusicVolume(0.2);
	Sleep(1000);
	m_soundSystem->changeMusic("./assets/PTSD-Anthem2.mp3", true);
	m_soundSystem->setMusicVolume(0.5);
	Sleep(1000);
	for (int k = 0; k < PTSD::ChannGroupCount; k++) {
		for (int l = 0; l < 5; l++) {
			if (l == 2) m_soundSystem->setChannelGroupVolume(1, 10);
			PTSD::Sound* oof = new PTSD::Sound("./assets/oof.mp3", k);
			oof->setVolume(0.2 * k * l + 1);
			m_soundSystem->playSound(oof);
			Sleep(500);
		}
	}
	std::cout << "Sound testing complete!!!\n";
}

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
	scriptingSystem->init();
	PTSD::LOG("All subsystems initialized");
	test_Sound(soundSystem);
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