#pragma once

#if defined(_MSC_VER)
	#ifdef _PTSDGRAPHICS
		#define GRAPHICSAPI  __declspec(dllexport)   // export DLL information
	#else
		#define GRAPHICSAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDLOG
		#define GRAPHICSAPI __attribute__((visibility("default")))
	#else
		#define GRAPHICSAPI
	#endif 
#endif 


namespace PTSD {
	class GraphicsImplementation;
	class Camera;

	/**
	 * \brief Singleton Rendering Manger
	 */
	class GRAPHICSAPI Graphics {
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