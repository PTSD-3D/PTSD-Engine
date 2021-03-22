#include "PTSDUI.h"
#include <CEGUI/CEGUI.h>
#include <iostream>


int PTSD::UI::Init() {

	CEGUI::BasicImage("PTSD-UI-Test");
	std::cout << "Hello PTSD-UI" << '\n';

	return 0;
}