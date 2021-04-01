#include <iostream>
#include "PTSDUI.h"
#include "PTSDGraphics.h"
#include "UIImplementation.h"

namespace PTSD {

	UI* UI::mInstance = nullptr;

	int UI::init() {
		mImplementation = PTSD::UIImplementation::getInstance();
		mImplementation->init(PTSD::Graphics::getInstance()->getRenderWindow());
		return 0;
	}

	bool UI::render()
	{
		return mImplementation->render(PTSD::Graphics::getInstance()->getDeltaTime());
	}

	void UI::shutdown()
	{
		return mImplementation->shutdown();
	}
}
