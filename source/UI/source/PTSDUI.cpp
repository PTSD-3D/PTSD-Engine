#include <iostream>
#include "PTSDUI.h"
#include "PTSDGraphics.h"
#include "PTSDInput.h"
#include "UIImplementation.h"

namespace PTSD {

	UI* UI::mInstance = nullptr;

	int UI::init() {
		mImplementation = PTSD::UIImplementation::getInstance();
		inputInstance = PTSD::Input::getInstance();
		graphicsInstance = PTSD::Graphics::getInstance();
		mImplementation->init(graphicsInstance->getRenderWindow());
		registerForEvents();
		mImplementation->setMouseInitialPosition(inputInstance->getMousePosition());
		return 0;
	}

	/**
	 * \brief Renders a frame!
	 */
	bool UI::render()
	{
		inputUpdate();
		return mImplementation->render(graphicsInstance->getDeltaTime());
	}

	/**
	 * \brief Process the input from PTSD::Input instance
	 */
	void UI::inputUpdate()
	{
		if (inputInstance->mouseMotion()) mImplementation->injectMousePosition(
			inputInstance->getMousePosition());
		if (inputInstance->mouseLeftClick()) mImplementation->injectMouseLeftClick();
	}

	/**
	 * \brief Register for the events */
	void UI::registerForEvents()
	{
		/*bind(function, reference for the execution of the function, placeholder for parameters)*/
		auto function = std::bind(&PTSD::UI::testCallback, this, std::placeholders::_1);
		mImplementation->setEvent("PushButton", function);
	}

	/**
	 * \brief Test Callback function which changes text and image
	 */
	bool UI::testCallback(const CEGUI::EventArgs& e)
	{
		mImplementation->setStaticImage("PrettyImage","TaharezLook/MiniHorzScrollLeftHover");
		mImplementation->setText("PrettyText","ButtonTest pressed!");
		mImplementation->setLayoutVisible("DemoWindow", false);
		mImplementation->setMouseCursorVisible(false);
		return true;
	}

	void UI::shutdown()
	{
		return mImplementation->shutdown();
	}
}
