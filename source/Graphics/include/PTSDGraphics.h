#pragma once


namespace Ogre {
	class RenderWindow;
}

namespace PTSD {
	class GraphicsImplementation;
	class Camera;

	/**
	 * \brief Singleton Rendering Manger
	 */
	class Graphics {
	private:
		static Graphics* mInstance;
		GraphicsImplementation* mImplementation = nullptr;//private Implementation
	public:
		Graphics() = default;

		~Graphics() = default;

		static Graphics* getInstance()
		{
			if (mInstance == nullptr)
				mInstance = new Graphics();
			return mInstance;
		}
		int init();
		bool renderFrame();
		Camera* getCam();
		Ogre::RenderWindow* getRenderWindow() const;
		float getWindowWidth() const;
		float getWindowHeight() const;
		double getDeltaTime();
	};
}