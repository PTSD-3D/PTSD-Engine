#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDUI.h"

int main()
{
	PTSD::test();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	m_LogSystem->Init();
	
	PTSD::UI* m_UISystem = new PTSD::UI();
	m_UISystem->Init();
}
