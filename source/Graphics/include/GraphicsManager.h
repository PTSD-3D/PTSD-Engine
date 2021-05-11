#pragma once
#include "PTSDAssert.h"

class SDL_Window;

namespace Ogre {
	class RenderWindow;
}

namespace PTSD {
	class GraphicsImplementation;
	class Camera;

	/**
	 * \brief Singleton Rendering Manger
	 */
	class GraphicsManager {
	private:
		static GraphicsManager* mInstance;
		GraphicsImplementation* mImplementation = nullptr;//private Implementation
	public:
		GraphicsManager() = default;

		~GraphicsManager() = default;

		static GraphicsManager* getInstance()
		{
			PTSD_ASSERT(mInstance != nullptr, "Renderer singleton accessed before init");
			return mInstance;
		}
		static int init();
		bool renderFrame();
		Camera* getCam();
		Ogre::RenderWindow* getRenderWindow() const;
		SDL_Window* getSDLWindow() const;
		float getWindowWidth() const;
		float getWindowHeight() const;
		double getDeltaTime();
		void setMouseLocked(bool locked);
		void setSceneSkybox(bool enabled, const std::string& material, float distance, bool renderFirst );
		void setSceneSkydome(bool enabled, const std::string& material, unsigned int curvature, unsigned int tiledRepetitions);
	};
}