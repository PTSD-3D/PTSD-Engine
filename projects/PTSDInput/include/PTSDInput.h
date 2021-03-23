#pragma once
#ifdef _PTSDINPUT
#define INPUTAPI  __declspec(dllexport)   // export DLL information

#else
#define INPUTAPI  __declspec(dllimport)   // import DLL information

#endif 

namespace PTSD {
	class INPUTAPI Input {
	private:

	public:
		static int Init();
		~Input() {}
		Input() {}
	};
}