#include <iostream>
#include "PTSDUI.h"
#include "PTSDGraphics.h"
#include "UIImplementation.h"

namespace PTSD {

	UI* UI::mInstance = nullptr;

	int UI::init() {
		mImpl = PTSD::UIImplementation::getInstance();
		mImpl->init(PTSD::Graphics::getInstance()->getRenderWindow());
		return 0;
	}

	bool UI::render()
	{
		return mImpl->render();
	}

	void UI::shutdown()
	{
		return mImpl->shutdown();
	}
}
