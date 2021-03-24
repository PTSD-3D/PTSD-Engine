#pragma once
#ifdef _PTSDSCRIPTING
#define SCRIPTINGAPI  __declspec(dllexport)   // export DLL information

#else
#define SCRIPTINGAPI  __declspec(dllimport)   // import DLL information

#endif 

namespace PTSD {
	class SCRIPTINGAPI Scripting {
	private:

	public:
		static int Init();
		~Scripting() {}
		Scripting() {}
	};
}