#include <iostream>
#include "test.h"

#include "PTSDInput.h"

int main()
{
	PTSD::test();

	PTSD::Input* m_InputSystem = new PTSD::Input();
	m_InputSystem->Init();
}
