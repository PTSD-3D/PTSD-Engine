#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"
#include "PTSDUI.h"
#include "PTSDInput.h"

int main()
{
	PTSD::test();

	PTSD::Input* m_InputSystem = new PTSD::Input();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = new PTSD::Graphics();
	PTSD::Scripting* m_ScriptingSystem = new PTSD::Scripting();
	PTSD::UI* m_UISystem = new PTSD::UI();

	m_InputSystem->Init();
	m_LogSystem->Init();
	m_GraphicsSystem->Init();
	m_ScriptingSystem->Init();
	m_UISystem->Init();
}
