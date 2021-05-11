#include <iostream>
#include "GraphicsManager.h"
#include "GraphicsImplementation.h"

namespace PTSD {
	GraphicsManager* GraphicsManager::mInstance = nullptr;
	int GraphicsManager::init() {
		PTSD_ASSERT(mInstance == nullptr, "GraphicsManager alredy initialized");
		mInstance = new GraphicsManager();
		mInstance->mImplementation = PTSD::GraphicsImplementation::getInstance();
		mInstance->mImplementation->init();
		return 0;
	}

	/**
	 * \brief Renders a frame!
	 * \return True on success
	 */
	bool GraphicsManager::renderFrame()
	{
		return mImplementation->renderFrame();
	}

	Camera* GraphicsManager::getCam()
	{
		return mImplementation->getCamera();
	}
	Ogre::RenderWindow* GraphicsManager::getRenderWindow() const
	{
		return mImplementation->getRenderWindow();
	}

	float GraphicsManager::getWindowWidth() const
	{
		return  mImplementation->getWindowWidth();
	}

	float GraphicsManager::getWindowHeight() const
	{
		return getWindowHeight();
	}

	class SDL_Window* GraphicsManager::getSDLWindow() const
	{
		return mImplementation->getSDLWindow();
	}

	double GraphicsManager::getDeltaTime()
	{
		return mImplementation->getDeltaTime();
	}
	void GraphicsManager::setMouseLocked(bool locked)
	{
		mImplementation->setMouseLocked(locked);
	}

	void GraphicsManager::setSceneSkybox(bool enabled, const std::string& material, float distance, bool renderFirst )
	{
		mImplementation->setSceneSkybox(enabled, material, distance, renderFirst);
	}
	void GraphicsManager::setSceneSkydome(bool enabled, const std::string& material, unsigned int curvature, unsigned int tiledRepetitions)
	{
		mImplementation->setSceneSkydome(enabled, material, curvature, tiledRepetitions);
	}
}
