#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDInput.h"

int main()
{
	PTSD::test();

	PTSD::Input* m_InputSystem = new PTSD::Input();
	m_InputSystem->Init();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = new PTSD::Graphics();
	PTSD::Scripting* m_ScriptingSystem = new PTSD::Scripting();
	m_LogSystem->Init();
	m_GraphicsSystem->Init();
	m_ScriptingSystem->Init();
}
