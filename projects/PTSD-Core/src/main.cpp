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
#include "Vec2.h"
#include "PTSDkeys.h"

int main()
{
	PTSD::Input* m_InputSystem = new PTSD::Input();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = PTSD::Graphics::getInstance();
	PTSD::Scripting* m_ScriptingSystem = new PTSD::Scripting();
	PTSD::PTSDPhysics* m_physicsSystem = new PTSD::PTSDPhysics();
	PTSD::UI* m_UISystem = new PTSD::UI();
	PTSD::PTSDSound* m_soundSystem = new PTSD::PTSDSound();
	PTSD::PTSDPhysics* physicsSystem = new PTSD::PTSDPhysics();

#ifdef _DEBUG
	m_LogSystem->Init(PTSD::Trace);
#else
	m_LogSystem->Init(PTSD::Warning);
#endif
	PTSD::LOG("Beginning Initialization");
	m_soundSystem->Init();
	m_InputSystem->Init();
	physicsSystem->Init();
	m_GraphicsSystem->Init();
	m_InputSystem->Init();
	m_ScriptingSystem->Init();
	PTSD::LOG("All subsystems initialized");

	PTSD::Camera* myCam = m_GraphicsSystem->getCam();
	bool exit = false;

	while(!exit)
	{
		m_InputSystem->update();

		m_GraphicsSystem->renderFrame();
		m_GraphicsSystem->getCam()->translate({ 0,0,0.1 });

		exit = m_InputSystem->keyPressed(SCANCODE_A);
		//exit = m_InputSystem->ControllerButtonReleased(0,CONTROLLER_BUTTON_A);
		//exit = m_InputSystem->mouseWheelClick();

		/*Vector2D pos = m_InputSystem->controllerLeftAxis(0);
		std::cout << pos.x << " " << pos.y << std::endl;*/
		//std::cout << m_InputSystem->controllerLeftTrigger(0) << std::endl;
	}
}
