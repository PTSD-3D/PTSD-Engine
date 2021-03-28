#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDPhysics.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDUI.h"

#include "PTSDInput.h"

int main()
{

	PTSD::Input* m_InputSystem = new PTSD::Input();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = PTSD::Graphics::getInstance();
	PTSD::Scripting* m_ScriptingSystem = new PTSD::Scripting();
	PTSD::UI* m_UISystem = new PTSD::UI();
	PTSD::PTSDPhysics* physicsSystem = new PTSD::PTSDPhysics();


#ifdef _DEBUG
	m_LogSystem->Init(PTSD::Trace);
#else
	m_LogSystem->Init(PTSD::Warning);
#endif
	PTSD::LOG("Beginning Initialization");
	m_InputSystem->Init();
	physicsSystem->test();
	m_GraphicsSystem->Init();
	m_ScriptingSystem->Init();
	PTSD::LOG("All subsystems initialized");


	while(true)
	{
		m_GraphicsSystem->renderFrame();
	}
}
