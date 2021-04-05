#include <iostream>
#include "PTSDUI.h"
#include "PTSDGraphics.h"
#include "PTSDInput.h"
#include "UIImplementation.h"

namespace PTSD {

	UI* UI::mInstance = nullptr;

	int UI::init() {
		mImplementation = PTSD::UIImplementation::getInstance();
		mImplementation->init(PTSD::Graphics::getInstance()->getRenderWindow());
		mImplementation->setMouseInitialPosition(PTSD::Input::getInstance()->getMousePos());
		return 0;
	}

	bool UI::render()
	{
		if (PTSD::Input::getInstance()->mouseMotion()) mImplementation->injectMousePosition(
		PTSD::Input::getInstance()->getMousePos());
		if (PTSD::Input::getInstance()->mouseLeftClick()) mImplementation->injectMouseLeftClick();
		return mImplementation->render(PTSD::Graphics::getInstance()->getDeltaTime());
	}

	void UI::shutdown()
	{
		return mImplementation->shutdown();
	}
}
