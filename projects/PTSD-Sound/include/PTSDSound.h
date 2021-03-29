#pragma once

#if defined(_MSC_VER)
	#ifdef _PTSDSOUND
		#define SOUNDAPI  __declspec(dllexport)   // export DLL information
	#else
		#define SOUNDAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDSOUND
		#define SOUNDAPI __attribute__((visibility("default")))
	#else
		#define SOUNDAPI
	#endif 
#endif 

namespace PTSD {
	class PTSDSound
	{
	public:
		PTSDSound() {};
		int SOUNDAPI test();
	};
}