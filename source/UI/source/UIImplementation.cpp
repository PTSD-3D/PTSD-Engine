#include "UIImplementation.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/Event.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <OgreRenderWindow.h>

#include <iostream>

namespace PTSD {

	UIImplementation* UIImplementation::mInstance = nullptr;

	int UIImplementation::init(Ogre::RenderWindow* mRenderWindow)
	{
		renderer = &CEGUI::OgreRenderer::bootstrapSystem(*mRenderWindow);

		windowMngr = &CEGUI::WindowManager::getSingleton();

		system = &CEGUI::System::getSingleton();

		createRoot();

		loadResources();

		system->getDefaultGUIContext().setDefaultFont("DejaVuSans-12");

		CEGUI::DefaultLogger::getSingletonPtr()->setLogFilename("logs/CEGUI.log");
		std::cout << "SIZE" << renderer->getDisplaySize().d_height << '\n';

		test();

		return 0;
	}

	bool UIImplementation::render(double deltaTime)
	{
		system->getDefaultGUIContext().injectTimePulse(deltaTime);
		system->getDefaultGUIContext().injectMouseMove(0.1, 0);
		system->renderAllGUIContexts();

		return false;
	}

	void UIImplementation::shutdown()
	{
		windowMngr->destroyAllWindows();
		mRoot = nullptr;
	}

	void UIImplementation::loadScheme(std::string filename)
	{
		CEGUI::SchemeManager::getSingleton().createFromFile(filename);
	}

	void UIImplementation::loadFont(std::string filename)
	{
		CEGUI::FontManager::getSingleton().createFromFile(filename);
	}

	void UIImplementation::loadResources()
	{
		loadScheme("TaharezLook.scheme");
		loadFont("DejaVuSans-12.font");
	}

	void UIImplementation::createRoot()
	{
		mRoot = windowMngr->createWindow("DefaultWindow", "MasterRoot");
		system->getDefaultGUIContext().setRootWindow(mRoot);
	}

	void UIImplementation::createWindowStaticImage(std::string name, std::string source, Vector2D position, Vector2D size)
	{
		CEGUI::Window* myImageWindow = windowMngr->createWindow("TaharezLook/StaticImage", name);
		myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, position.getX()), CEGUI::UDim(0, position.getY())));
		myImageWindow->setSize(CEGUI::USize(CEGUI::UDim(0, size.getX()), CEGUI::UDim(0, size.getY())));
		myImageWindow->setProperty("Image", source);
		mRoot->addChild(myImageWindow);
	}

	void UIImplementation::setMouseCursor(std::string name)
	{
		system->getDefaultGUIContext().getMouseCursor().setDefaultImage(name);
		setMouseCursorVisible(true);
	}

	void UIImplementation::setMouseCursorVisible(bool active)
	{
		if(active) system->getDefaultGUIContext().getMouseCursor().show();
		else system->getDefaultGUIContext().getMouseCursor().hide();
	}
	void UIImplementation::test()
	{
		

		setMouseCursor("TaharezLook/MouseArrow");

		createWindowStaticImage("PrettyWindow", "TaharezLook/UpArrow", Vector2D(renderer->getDisplaySize().d_width/2 , renderer->getDisplaySize().d_height/2), Vector2D(50, 50));
	}
}


