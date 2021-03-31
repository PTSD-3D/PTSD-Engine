#include <iostream>
#include "PTSDUI.h"
#include "UIImpl.h"

namespace PTSD {

	UI* UI::mInstance = nullptr;

	int UI::Init() {
		mImpl = PTSD::UIImpl::getInstance();
		mImpl->Init();
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

