#include "UIImplementation.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/Event.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <OgreRenderWindow.h>

#include <iostream>

namespace PTSD {

	UIImplementation* UIImplementation::mInstance = nullptr;

	/**
	 * \brief Creates an instance of the Ogre3d Render interface between Ogre3d and CEGUI,
	 * gets system, window manager and OgreRenderer references,
	 * create a root and load resources
	 * \param mRenderWindow target reference
	 */
	int UIImplementation::init(Ogre::RenderWindow* mRenderWindow)
	{
		renderer = &CEGUI::OgreRenderer::bootstrapSystem(*mRenderWindow);

		windowMngr = &CEGUI::WindowManager::getSingleton();

		system = &CEGUI::System::getSingleton();

		createRoot();

		loadResources();

		system->getDefaultGUIContext().setDefaultFont("DejaVuSans-12");

		CEGUI::DefaultLogger::getSingletonPtr()->setLogFilename("logs/CEGUI.log");

		test();

		return 0;
	}

	/**
	 * \brief Render GUIContexts and synchronize CEGUI System with Ogre3D
	 */
	bool UIImplementation::render(double deltaTime)
	{
		system->getDefaultGUIContext().injectTimePulse(deltaTime);
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

	void UIImplementation::loadLayout(std::string filename)
	{
		CEGUI::Window* layout = windowMngr->loadLayoutFromFile(filename);
		mRoot->addChild(layout);
	}

	void UIImplementation::loadResources()
	{
		loadScheme("TaharezLook.scheme");
		loadFont("DejaVuSans-12.font");
		//loadLayout("TaharezLookOverview.layout");
	}

	/**
	 * \brief Creates MasterRoot
	 */
	void UIImplementation::createRoot()
	{
		mRoot = windowMngr->createWindow("DefaultWindow", "MasterRoot");
		system->getDefaultGUIContext().setRootWindow(mRoot);
	}

	void UIImplementation::createText(std::string name, std::string text, Vector2D position, Vector2D size)
	{
		CEGUI::Window* myTextWindow = windowMngr->createWindow("TaharezLook/StaticText", name);
		myTextWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, position.getX()), CEGUI::UDim(0, position.getY())));
		myTextWindow->setSize(CEGUI::USize(CEGUI::UDim(0, size.getX()), CEGUI::UDim(0, size.getY())));
		myTextWindow->setProperty("Text", text);
		mRoot->addChild(myTextWindow);
	}

	void UIImplementation::createStaticImage(std::string name, std::string source, Vector2D position, Vector2D size)
	{
		CEGUI::Window* myImageWindow = windowMngr->createWindow("TaharezLook/StaticImage", name);
		myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, position.getX()), CEGUI::UDim(0, position.getY())));
		myImageWindow->setSize(CEGUI::USize(CEGUI::UDim(0, size.getX()), CEGUI::UDim(0, size.getY())));
		myImageWindow->setProperty("Image", source);
		mRoot->addChild(myImageWindow);
	}

	void UIImplementation::createButton(std::string name, std::string text, Vector2D position, Vector2D size)
	{
		CEGUI::PushButton* myButtonWindow = static_cast<CEGUI::PushButton*>(windowMngr->createWindow("TaharezLook/Button", name));
		myButtonWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, position.getX()), CEGUI::UDim(0, position.getY())));
		myButtonWindow->setSize(CEGUI::USize(CEGUI::UDim(0, size.getX()), CEGUI::UDim(0, size.getY())));
		myButtonWindow->setText(text);
		mRoot->addChild(myButtonWindow);
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

	void UIImplementation::setMouseInitialPosition(Vector2D mousePosition)
	{
		system->getDefaultGUIContext().getMouseCursor().setPosition(CEGUI::Vector2f(mousePosition.getX(), mousePosition.getY()));
	}

	void UIImplementation::setEvent(std::string name, std::function<bool(const CEGUI::EventArgs&)> function)
	{
		CEGUI::PushButton* myButton = getPushButton(name);
		myButton->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(function));
	}

	void UIImplementation::setText(std::string name, std::string text)
	{
		CEGUI::Window* myWindow = mRoot->getChild(name);
		myWindow->setText(text);
	}

	void UIImplementation::setStaticImage(std::string name, std::string image)
	{
		CEGUI::Window* myWindow = mRoot->getChild(name);
		myWindow->setProperty("Image", image);
	}

	CEGUI::PushButton* UIImplementation::getPushButton(std::string name)
	{
		return static_cast<CEGUI::PushButton*>(mRoot->getChild(name));
	}

	void UIImplementation::injectMousePosition(Vector2D mousePosition)
	{
		system->getDefaultGUIContext().injectMouseMove(mousePosition.getX() - lastMousePosition.getX(), mousePosition.getY() - lastMousePosition.getY());
		lastMousePosition = mousePosition;
	}

	void UIImplementation::injectMouseLeftClick()
	{
		system->getDefaultGUIContext().injectMouseButtonClick(CEGUI::LeftButton);
	}

	void UIImplementation::test()
	{
		setMouseCursor("TaharezLook/MouseArrow");

		createStaticImage("PrettyImage", "TaharezLook/UpArrow", Vector2D(renderer->getDisplaySize().d_width/2 , renderer->getDisplaySize().d_height/2), Vector2D(50, 50));
		createText("PrettyText", "Plane text", Vector2D(renderer->getDisplaySize().d_width/1.5 , renderer->getDisplaySize().d_height/2), Vector2D(150, 50));
		createButton("PushButton", "TestButton", Vector2D(renderer->getDisplaySize().d_width / 3, renderer->getDisplaySize().d_height / 2), Vector2D(100, 50));
	}
}


