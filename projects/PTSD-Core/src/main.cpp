#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDGraphics.h"
#include "PTSDScripting.h"

int main()
{
	PTSD::test();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = new PTSD::Graphics();
	PTSD::Scripting* m_ScriptingSystem = new PTSD::Scripting();
	m_LogSystem->Init();
	m_GraphicsSystem->Init();
	m_ScriptingSystem->Init();
}
