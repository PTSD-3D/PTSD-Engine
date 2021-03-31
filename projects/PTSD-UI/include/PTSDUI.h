#pragma once
#if defined(_MSC_VER)
	#ifdef _PTSDUI
		#define UIAPI  __declspec(dllexport)   // export DLL information
	#else
		#define UIAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDUI
		#define UIAPI __attribute__((visibility("default")))
	#else
		#define UIAPI 
	#endif 
#endif

namespace Ogre {
	class RenderWindow;
}

namespace PTSD {
	class UIImplementation;

	class UIAPI UI {
	private:
		static UI* mInstance;
		UIImplementation* mImpl = nullptr; //private implementation
		
	public:
		static UI* getInstance()
		{
			if (mInstance == nullptr)
				mInstance = new UI();
			return mInstance;
		}

		int Init(Ogre::RenderWindow* mRenderWindow);
		bool Render();
		void Shutdown();

		UI() = default;
		~UI() = default;
	};
}
