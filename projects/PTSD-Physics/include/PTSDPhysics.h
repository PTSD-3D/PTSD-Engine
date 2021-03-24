#pragma once
#ifdef _PTSDPHYS
#define PHYSAPI  __declspec(dllexport)   // export DLL information

#else
#define PHYSAPI  __declspec(dllimport)   // import DLL information

#endif 

namespace PTSD {
	class PTSDPhysics
	{
		public:
			PTSDPhysics() {};
			int PHYSAPI init();
	};
}