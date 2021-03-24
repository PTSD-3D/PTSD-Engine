#pragma once
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#ifdef _PTSDPHYS
#define PHYSAPI  __declspec(dllexport)   // export DLL information

#else
#define PHYSAPI  __declspec(dllimport)   // import DLL information

#endif 

namespace PTSD {
	class PTSDPhysics
	{
		public:
			int PHYSAPI init();
	};
}