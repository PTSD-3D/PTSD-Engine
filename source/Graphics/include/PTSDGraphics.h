#pragma once


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
	};
}