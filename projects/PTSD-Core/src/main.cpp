#include <iostream>
#include "test.h"
#include "PTSDLog.h"

#include "PTSDInput.h"

int main()
{
	PTSD::test();

	PTSD::Input* m_InputSystem = new PTSD::Input();
	m_InputSystem->Init();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	m_LogSystem->Init();
}
