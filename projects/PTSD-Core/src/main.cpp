#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"

#include "PTSDInput.h"

int main()
{
	PTSD::LOG("Beginning Initialization");

	PTSD::Input* m_InputSystem = new PTSD::Input();
	m_InputSystem->Init();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = new PTSD::Graphics();
	PTSD::Scripting* m_ScriptingSystem = new PTSD::Scripting();
	PTSD::PTSDPhysics* physicsSystem = new PTSD::PTSDPhysics();

	PTSD::LOG("All subsystems initialized");

	
	m_LogSystem->Init(PTSD::Info);

	physicsSystem->test();
	m_GraphicsSystem->Init();
	m_ScriptingSystem->Init();
}
