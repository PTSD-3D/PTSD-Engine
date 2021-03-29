#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDSound.h"
#include "PTSDInput.h"

int main()
{
	PTSD::test();

	PTSD::Input* m_InputSystem = new PTSD::Input();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = new PTSD::Graphics();
	PTSD::Scripting* m_ScriptingSystem = new PTSD::Scripting();
	PTSD::PTSDPhysics* physicsSystem = new PTSD::PTSDPhysics();
	PTSD::PTSDSound* soundSystem = new PTSD::PTSDSound();
	
	soundSystem->test();
	m_LogSystem->Init();
	physicsSystem->test();
	m_GraphicsSystem->Init();
	m_ScriptingSystem->Init();
	m_InputSystem->Init();
}
