#include "UIImplementation.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

namespace PTSD {

	UIImplementation* UIImplementation::mInstance = nullptr;

	int UIImplementation::Init(Ogre::RenderWindow* mRenderWindow)
	{
		renderer = &CEGUI::OgreRenderer::bootstrapSystem();
		return 0;
	}

	bool UIImplementation::Render()
	{
		return false;
	}

	void UIImplementation::Shutdown()
	{
	}
}


