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
		
		setMouseCursor("TaharezLook/MouseArrow");

		createRoot();

		createWindowStaticImage("PrettyWindow", "TaharezLook/UpArrow",50,50);

		return 0;
	}

	bool UIImplementation::render(double deltaTime)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(deltaTime);
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(0.1, 0);
		CEGUI::System::getSingleton().renderAllGUIContexts();

		return false;
	}

	void UIImplementation::shutdown()
	{
		CEGUI::WindowManager::getSingleton().destroyAllWindows();
		delete mRoot;
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

	void UIImplementation::createWindowStaticImage(std::string name, std::string source, float xDim, float yDim)
	{
		CEGUI::Window* myImageWindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", name);
		myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.5, 0)));
		myImageWindow->setSize(CEGUI::USize(CEGUI::UDim(0, xDim), CEGUI::UDim(0, yDim)));
		myImageWindow->setProperty("Image", source);
		mRoot->addChild(myImageWindow);
	}

	void UIImplementation::setMouseCursor(std::string name)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(name);
		setMouseCursorVisible(true);
	}

	void UIImplementation::setMouseCursorVisible(bool active)
	{
		if(active) CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
		else CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
	}
}


