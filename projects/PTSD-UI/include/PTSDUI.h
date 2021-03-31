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

namespace PTSD {
	class UIAPI UI {
	private:
	public:
		UI() {}
		~UI() {}

		static int init();
	};
}
