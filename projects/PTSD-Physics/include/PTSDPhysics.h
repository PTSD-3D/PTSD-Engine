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
	class PhysicsImplementation;

	class PHYSAPI Physics
	{
	private:
		static Physics* mInstance;
		PhysicsImplementation* mImpl = nullptr; //private implementation

	public:
		static Physics* getInstance() {
			if (mInstance == nullptr)
				mInstance = new Physics();
			return mInstance;
		}

		void init();
		void update();
		void shutdown();

		Physics() = default;
		~Physics() = default;
	};
}