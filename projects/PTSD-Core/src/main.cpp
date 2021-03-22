#include <iostream>
#include "test.h"
#include "PTSDLog.h"

int main()
{
	PTSD::test();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	m_LogSystem->Init();
}
