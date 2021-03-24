#pragma once
#if defined(_MSC_VER)
	#ifdef _PTSDLOG
		#define LOGAPI  __declspec(dllexport)   // export DLL information
	#else
		#define LOGAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDLOG
		#define LOGAPI __attribute__((visibility("default")))
	#else
		#define LOGAPI
	#endif 
#endif 


namespace PTSD {
	class LOGAPI Log {
	private:

	public:
		static int Init();
		~Log(){}
		Log(){}
	};
}