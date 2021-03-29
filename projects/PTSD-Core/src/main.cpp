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
	PTSD::PTSDPhysics* m_physicsSystem = new PTSD::PTSDPhysics();
	PTSD::UI* m_UISystem = new PTSD::UI();
	PTSD::PTSDSound* m_soundSystem = new PTSD::PTSDSound();
	PTSD::PTSDPhysics* physicsSystem = new PTSD::PTSDPhysics();

	
	m_LogSystem->Init(PTSD::Info);
	PTSD::LOG("Beginning Initialization");
	m_soundSystem->Init();
	m_InputSystem->Init();
	physicsSystem->Init();
	m_GraphicsSystem->Init();
	m_ScriptingSystem->Init();
	PTSD::LOG("All subsystems initialized");
}
