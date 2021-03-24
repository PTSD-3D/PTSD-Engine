#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDGraphics.h"

int main()
{
	PTSD::test();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = new PTSD::Graphics();
	m_LogSystem->Init();
	m_GraphicsSystem->Init();
}
