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
	PTSD::Input* m_InputSystem = new PTSD::Input();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = PTSD::Graphics::getInstance();
	PTSD::Scripting* scriptingSystem = new PTSD::Scripting();
	PTSD::PTSDPhysics* m_physicsSystem = new PTSD::PTSDPhysics();
	PTSD::UI* m_UISystem = new PTSD::UI();
	PTSD::PTSDSound* m_soundSystem = new PTSD::PTSDSound();

#ifdef _DEBUG
	m_LogSystem->Init(PTSD::Trace);
#else
	m_LogSystem->Init(PTSD::Warning);
#endif
	PTSD::LOG("Beginning Initialization");
	m_soundSystem->Init();
	m_InputSystem->Init();
	m_physicsSystem->Init();
	m_GraphicsSystem->Init();
	scriptingSystem->init();
	PTSD::LOG("All subsystems initialized");

	PTSD::Camera* myCam = m_GraphicsSystem->getCam();
	while(true)
	{
		m_GraphicsSystem->renderFrame();
		m_GraphicsSystem->getCam()->translate({ 0,0,0.1 });
	}
}
