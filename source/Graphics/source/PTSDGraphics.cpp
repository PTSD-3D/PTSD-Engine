#include <iostream>
#include "PTSDGraphics.h"
#include "GraphicsImplementation.h"

namespace PTSD {
	Graphics* Graphics::mInstance = nullptr;
	int Graphics::init() {
		mImplementation = PTSD::GraphicsImplementation::getInstance();
		mImplementation->init();
		return 0;
	}

	/**
	 * \brief Renders a frame!
	 * \return True on success
	 */
	bool Graphics::renderFrame()
	{
		return mImplementation->renderFrame();
	}

	Camera* Graphics::getCam()
	{
		return mImplementation->getCamera();
	}

	Ogre::RenderWindow* Graphics::getRenderWindow() const
	{
		return mImplementation->getRenderWindow();
	}

	SDL_Window* Graphics::getSDLWindow() const
	{
		return mImplementation->getSDLWindow();
	}

	float Graphics::getWindowWidth() const
	{
		return mImplementation->getWindowWidth();
	}

	float Graphics::getWindowHeight() const
	{
		return mImplementation->getWindowHeight();
	}

	double Graphics::getDeltaTime()
	{
		return mImplementation->getDeltaTime();
	}
}
