#include "PTSDUI.h"
#include <CEGUI/CEGUI.h>
#include <iostream>


int PTSD::UI::init() {
	std::cout << "UI system initialized\n";
	CEGUI::BasicImage image("PTSD-UI-Test\n");
	std::cout << image.getName();

	return 0;
}