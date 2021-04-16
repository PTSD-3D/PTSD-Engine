#pragma once
#include "PTSDAssert.h"


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
		double getDeltaTime();
	};
}