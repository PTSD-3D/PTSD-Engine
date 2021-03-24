#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDGraphics.h"
#include "PTSDUI.h"

int main()
{
	PTSD::test();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	PTSD::Graphics* m_GraphicsSystem = new PTSD::Graphics();
	PTSD::UI* m_UISystem = new PTSD::UI();
	m_LogSystem->Init();
	m_GraphicsSystem->Init();
	m_UISystem->Init();
}
