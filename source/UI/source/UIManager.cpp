#include <iostream>
#include "UIManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "UIImplementation.h"

namespace PTSD {

	UIManager* UIManager::mInstance = nullptr;

	int UIManager::init() {
		PTSD_ASSERT(mInstance == nullptr, "UIManager already initialized");
		mInstance = new UIManager();
		mInstance->mImplementation = PTSD::UIImplementation::getInstance();
		mInstance->inputInstance = PTSD::InputManager::getInstance();
		mInstance->graphicsInstance = PTSD::GraphicsManager::getInstance();
		mInstance->mImplementation->init(mInstance->graphicsInstance->getRenderWindow());
		mInstance->registerForEvents();
		mInstance->mImplementation->setMouseInitialPosition(mInstance->inputInstance->getMousePosition());
		return 0;
	}

	/**
	 * \brief Renders a frame!
	 */
	bool UIManager::render()
	{
		inputUpdate();
		return mImplementation->render(graphicsInstance->getDeltaTime());
	}

	/**
	 * \brief Process the input from PTSD::Input instance
	 */
	void UIManager::inputUpdate()
	{
		if (inputInstance->mouseMotion()) mImplementation->injectMousePosition(
			inputInstance->getMousePosition());
		if (inputInstance->mouseLeftClick()) mImplementation->injectMouseLeftClick();
	}

	/**
	 * \brief Register for the events */
	void UIManager::registerForEvents()
	{
		/*bind(function, reference for the execution of the function, placeholder for parameters)*/
		auto function = std::bind(&PTSD::UIManager::testCallback, this, std::placeholders::_1);
		mImplementation->setEvent("PushButton", function);
	}

	/**
	 * \brief Test Callback function which changes text and image
	 */
	bool UIManager::testCallback(const CEGUI::EventArgs& e)
	{
		mImplementation->setLayoutVisible("PrettyImage", false);
		mImplementation->setLayoutVisible("PrettyText", false);
		mImplementation->setLayoutVisible("PushButton", false);
		mImplementation->setLayoutVisible("DemoWindow", false);
		mImplementation->setMouseCursorVisible(false);
		return true;
	}

	void UIManager::shutdown()
	{
		return mImplementation->shutdown();
	}
}
