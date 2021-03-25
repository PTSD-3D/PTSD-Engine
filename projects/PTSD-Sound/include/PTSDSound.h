#pragma once
#ifdef _PTSDSOUND
#define SOUNDAPI  __declspec(dllexport)   // export DLL information

#else
#define SOUNDAPI  __declspec(dllimport)   // import DLL information

#endif 

namespace PTSD {
	class PTSDSound
	{
	public:
		PTSDSound() {};
		int SOUNDAPI test();
	};
}