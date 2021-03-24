#include <iostream>
#include "test.h"
#include "PTSDLog.h"
#include "PTSDPhysics.h"

int main()
{
	PTSD::test();
	PTSD::Log* m_LogSystem = new PTSD::Log();
	m_LogSystem->Init();

	PTSD::PTSDPhysics* physicsSystem = new PTSD::PTSDPhysics();
	physicsSystem->test();
}
