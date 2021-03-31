#pragma once

#if defined(_MSC_VER)
	#ifdef _PTSDSCRIPTING
		#define SCRIPTINGAPI  __declspec(dllexport)   // export DLL information
	#else
		#define SCRIPTINGAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDSCRIPTING
		#define SCRIPTINGAPI __attribute__((visibility("default")))
	#else
		#define SCRIPTINGAPI
	#endif 
#endif 

namespace PTSD {
	class SCRIPTINGAPI Scripting {
	private:

	public:
		Scripting() {}

		~Scripting() {}
		
		void init();
	};
}