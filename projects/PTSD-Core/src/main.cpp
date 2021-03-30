#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDSound.h"
#include "PTSDUI.h"

#include "PTSDInput.h"

int main()
{
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Input* m_InputSystem = new PTSD::Input();
	PTSD::Graphics* m_GraphicsSystem = new PTSD::Graphics();
	PTSD::Scripting* m_ScriptingSystem = new PTSD::Scripting();
	PTSD::Physics* m_PhysicsSystem = PTSD::Physics::getInstance();
	PTSD::UI* m_UISystem = new PTSD::UI();
	PTSD::PTSDSound* m_soundSystem = new PTSD::PTSDSound();

	
	m_LogSystem->Init(PTSD::Info);
	PTSD::LOG("Beginning Initialization");
	m_soundSystem->Init();
	//m_InputSystem->Init();
	m_PhysicsSystem->Init();
	m_GraphicsSystem->Init();
	m_ScriptingSystem->Init();
	PTSD::LOG("All subsystems initialized");

	while (true){
		m_PhysicsSystem->Update();
	}
}
