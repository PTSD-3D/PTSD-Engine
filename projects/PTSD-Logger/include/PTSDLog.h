#pragma once
#ifdef _PTSDLOG
#define LOGAPI  __declspec(dllexport)   // export DLL information

#else
#define LOGAPI  __declspec(dllimport)   // import DLL information

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