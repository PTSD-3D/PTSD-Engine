#pragma once
#if defined(_MSC_VER)
	#ifdef _PTSDPHYS
		#define PHYSAPI  __declspec(dllexport)   // export DLL information
	#else
		#define PHYSAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDPHYS
		#define PHYSAPI __attribute__((visibility("default")))
	#else
		#define PHYSAPI
	#endif 
#endif 

namespace PTSD {
	class PTSDPhysics
	{
		public:
			PTSDPhysics() {};
			int PHYSAPI test();
	};
}