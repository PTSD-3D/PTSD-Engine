#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDGraphics.h"

#include "PTSDInput.h"

int main()
{
	PTSD::test();

	PTSD::Input* m_InputSystem = new PTSD::Input();
	m_InputSystem->Init();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = new PTSD::Graphics();
	m_LogSystem->Init();
	m_GraphicsSystem->Init();
}
