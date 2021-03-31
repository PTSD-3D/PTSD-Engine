#pragma once
#if defined(_MSC_VER)
	#ifdef _PTSDINPUT
		#define INPUTAPI  __declspec(dllexport)   // export DLL information
	#else
		#define INPUTAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDINPUT
		#define INPUTAPI __attribute__((visibility("default")))
	#else
		#define INPUTAPI
	#endif 
#endif 


namespace PTSD {
	class INPUTAPI Input {
	private:

	public:
		Input() {}
		~Input() {}
		
		static int init();
	};
}