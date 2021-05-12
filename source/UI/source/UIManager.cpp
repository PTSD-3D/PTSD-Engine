#include "UIManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ScriptManager.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/Event.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/InputEvent.h>
#include <CEGUI/Window.h>

#include <OgreRenderWindow.h>

#include <iostream>

namespace PTSD {

	UIManager* UIManager::mInstance = nullptr;

	/**
	* \brief Creates an instance of the Ogre3d Render interface between Ogre3d and CEGUI,
	* gets system, window manager and OgreRenderer references,
	* create a root and load resources
	* \param mRenderWindow target reference
	*/

	int UIManager::init() {
		PTSD_ASSERT(mInstance == nullptr, "UIManager already initialized");
		mInstance = new UIManager();
		
		mInstance->initLogger();

		mInstance->renderer = &CEGUI::OgreRenderer::bootstrapSystem(*PTSD::GraphicsManager::getInstance()->getRenderWindow());

		mInstance->windowMngr = &CEGUI::WindowManager::getSingleton();

		mInstance->system = &CEGUI::System::getSingleton();

		mInstance->createRoot();

		return 0;
	}

	/**
	 * \brief Renders a frame!
	 *	Render GUIContexts and synchronize CEGUI System with Ogre3D
	 */
	bool UIManager::render()
	{
		inputUpdate();

		system->getDefaultGUIContext().injectTimePulse(PTSD::GraphicsManager::getInstance()->getDeltaTime());
		system->renderAllGUIContexts();
		return false;
	}

	/**
	 * \brief Process the input from PTSD::Input instance
	 */
	void UIManager::inputUpdate()
	{
		if (PTSD::InputManager::getInstance()->mouseMotion()) injectMousePosition(
			PTSD::InputManager::getInstance()->getMousePosition());
		if (PTSD::InputManager::getInstance()->isMouseButtonDown(Left)) injectMouseLeftClick();
	}

	void UIManager::shutdown()
	{
		windowMngr->destroyAllWindows();
		mRoot = nullptr;
	}

	/**
	* \brief Creates MasterRoot
	*/
	void UIManager::createRoot()
	{
		mRoot = windowMngr->createWindow("DefaultWindow", "MasterRoot");
		system->getDefaultGUIContext().setRootWindow(mRoot);
	}

	void UIManager::initLogger()
	{
		if (!CEGUI::Logger::getSingletonPtr())
			new CEGUI::DefaultLogger();

		CEGUI::Logger::getSingleton().setLogFilename("logs/CEGUI.log");
	}

	void UIManager::setupResources()
	{
		CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
		CEGUI::Font::setDefaultResourceGroup("Fonts");
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	}
	/**
	* \brief Test Callback function which changes text and image
	*/
	bool UIManager::OnButtonClick(const CEGUI::EventArgs& e)
	{
		const CEGUI::MouseEventArgs& we = static_cast<const CEGUI::MouseEventArgs&>(e);
		CEGUI::String senderID = we.window->getName();
		std::string s = senderID.c_str();
		if (umap.count(s)>=1)
		{
			mScriptManager->execute(umap[s]);
		}

		return true;
	}

	void UIManager::loadScheme(const std::string& filename)
	{
		CEGUI::SchemeManager::getSingleton().createFromFile(filename);
	}

	void UIManager::loadFont(const std::string& filename)
	{
		CEGUI::FontManager::getSingleton().createFromFile(filename);
	}

	void UIManager::loadLayout(const std::string& filename)
	{
		CEGUI::Window* layout = windowMngr->loadLayoutFromFile(filename);
		mRoot->addChild(layout);
		layout->setVisible(false);
	}

	void UIManager::loadUIFile(const std::string& path, UIFileType type)
	{
		switch (type)
		{
		case PTSD::UIFileType::Scheme:
			loadScheme(path);
			break;
		case PTSD::UIFileType::Font:
			loadFont(path);
			break;
		case PTSD::UIFileType::Layout:
			loadLayout(path);
			break;
		default:
			break;
		}
	}

	void UIManager::createText(const std::string& name, const std::string& text, Vector2D position, Vector2D size)
	{
		CEGUI::Window* myTextWindow = windowMngr->createWindow("TaharezLook/StaticText", name);
		myTextWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, position.getX()), CEGUI::UDim(0, position.getY())));
		myTextWindow->setSize(CEGUI::USize(CEGUI::UDim(0, size.getX()), CEGUI::UDim(0, size.getY())));
		myTextWindow->setProperty("Text", text);
		mRoot->addChild(myTextWindow);
	}

	void UIManager::createStaticImage(const std::string& name, const std::string& source, Vector2D position, Vector2D size)
	{
		CEGUI::Window* myImageWindow = windowMngr->createWindow("TaharezLook/StaticImage", name);
		myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, position.getX()), CEGUI::UDim(0, position.getY())));
		myImageWindow->setSize(CEGUI::USize(CEGUI::UDim(0, size.getX()), CEGUI::UDim(0, size.getY())));
		myImageWindow->setProperty("Image", source);
		mRoot->addChild(myImageWindow);
	}
	/**
	* \brief After creating a button, we associate default callbacks for a button
	*/
	void UIManager::createButton(const std::string& name, const std::string& text, Vector2D position, Vector2D size)
	{
		CEGUI::PushButton* myButtonWindow = static_cast<CEGUI::PushButton*>(windowMngr->createWindow("TaharezLook/Button", name));
		myButtonWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, position.getX()), CEGUI::UDim(0, position.getY())));
		myButtonWindow->setSize(CEGUI::USize(CEGUI::UDim(0, size.getX()), CEGUI::UDim(0, size.getY())));
		myButtonWindow->setText(text);
		mRoot->addChild(myButtonWindow);

		/*bind(function, reference for the execution of the function, placeholder for parameters)*/
		auto function = std::bind(&PTSD::UIManager::OnButtonClick, this, std::placeholders::_1);
		myButtonWindow->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(function));
	}

	void UIManager::setUIMouseCursor(const std::string& name)
	{
		mInstance->mouseCursorName = name;
		system->getDefaultGUIContext().getMouseCursor().setDefaultImage(name);
		setUIMouseCursorVisible(true);
		setUIMouseInitialPosition(PTSD::InputManager::getInstance()->getMousePosition());
	}

	void UIManager::setUIMouseCursorVisible(bool active)
	{
		if (active) system->getDefaultGUIContext().getMouseCursor().setDefaultImage(mouseCursorName);
		else system->getDefaultGUIContext().getMouseCursor().setDefaultImage(mouseCursorName + "Hidden");
	}

	void UIManager::setUIMouseInitialPosition(Vector2D mousePosition)
	{
		system->getDefaultGUIContext().getMouseCursor().setPosition(CEGUI::Vector2f(mousePosition.getX(), mousePosition.getY()));
	}

	void UIManager::setText(const std::string& name, const std::string& text)
	{
		CEGUI::Window* myWindow = mRoot->getChild(name);
		myWindow->setText(text);
	}

	void UIManager::setStaticImage(const std::string& name, const std::string& image)
	{
		CEGUI::Window* myWindow = mRoot->getChild(name);
		myWindow->setProperty("Image", image);
	}

	void UIManager::setWindowVisible(const std::string& name, bool visible)
	{
		CEGUI::Window* myWindow = mRoot->getChild(name);
		myWindow->setVisible(visible);
	}

	void UIManager::setButtonFunction(const std::string& name, const std::string& functionName)
	{
		umap[name] = functionName;
	}

	CEGUI::Window* UIManager::getWindow(const std::string name)
	{
		return mRoot->getChild(name);
	}

	CEGUI::PushButton* UIManager::getPushButton(const std::string& name)
	{
		return static_cast<CEGUI::PushButton*>(mRoot->getChild(name));
	}

	void UIManager::injectMousePosition(Vector2D mousePosition)
	{
		system->getDefaultGUIContext().injectMouseMove(mousePosition.getX() - lastMousePosition.getX(), mousePosition.getY() - lastMousePosition.getY());
		lastMousePosition = mousePosition;
	}

	void UIManager::injectMouseLeftClick()
	{
		system->getDefaultGUIContext().injectMouseButtonClick(CEGUI::LeftButton);
	}
}
