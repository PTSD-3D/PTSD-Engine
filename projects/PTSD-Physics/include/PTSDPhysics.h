#pragma once
#ifdef _PTSDPHYS
#define PHYSAPI  __declspec(dllexport)   // export DLL information

#else
#define PHYSAPI  __declspec(dllimport)   // import DLL information

#endif 

namespace PTSD {
	class PhysicsImpl;

	class PHYSAPI Physics
	{
	private:
		static Physics* mInstance;
		PhysicsImpl* mImpl = nullptr; //private implementation

	public:
		static Physics* getInstance() {
			if (mInstance == nullptr)
				mInstance = new Physics();
			return mInstance;
		}

		void Init();
		void Update();
		void Shutdown();

		Physics() = default;
		~Physics() = default;
	};
}