#include <iostream>
#include "PTSDUI.h"
#include "UIImpl.h"

namespace PTSD {

	UI* UI::mInstance = nullptr;

	int UI::Init(Ogre::RenderWindow* mRenderWindow) {
		mImpl = PTSD::UIImpl::getInstance();
		mImpl->Init(mRenderWindow);
		return 0;
	}

	bool UI::Render()
	{
		return mImpl->Render();
	}

	void UI::Shutdown()
	{
		return mImpl->Shutdown();
	}
}

