#include "UIImplementation.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/Event.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <OgreRenderWindow.h>

namespace PTSD {

	UIImplementation* UIImplementation::mInstance = nullptr;

	int UIImplementation::init(Ogre::RenderWindow* mRenderWindow)
	{
		renderer = &CEGUI::OgreRenderer::bootstrapSystem(*mRenderWindow);

		loadScheme("TaharezLook.scheme");
		loadFont("DejaVuSans-12.font");

		CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

		createRoot();

		CEGUI::Window* myImageWindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "PrettyWindow");
		myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.5, 0)));
		myImageWindow->setSize(CEGUI::USize(CEGUI::UDim(0, 150), CEGUI::UDim(0, 100)));
		myImageWindow->setProperty("Image", "TaharezLook/full_image");
		CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(myImageWindow);

		return 0;
	}

	bool UIImplementation::render()
	{
		return false;
	}

	void UIImplementation::shutdown()
	{
	}

	void UIImplementation::loadScheme(std::string filename)
	{
		CEGUI::SchemeManager::getSingleton().createFromFile(filename);
	}
	void UIImplementation::loadFont(std::string filename)
	{
		CEGUI::FontManager::getSingleton().createFromFile(filename);
	}
	void UIImplementation::createRoot()
	{
		mRoot = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "MasterRoot");
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
	}
}


