#pragma once
#if defined(_MSC_VER)
	#ifdef _PTSDLOG
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
	class GRAPHICSAPI Graphics {
	private:

	public:
		static int Init();
		~Graphics() {}
		Graphics() {}
	};
}