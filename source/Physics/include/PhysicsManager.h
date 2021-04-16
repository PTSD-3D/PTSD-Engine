#pragma once
#include "PTSDAssert.h"

namespace PTSD {
	class PhysicsImplementation;

	class PhysicsManager
	{
	private:
		static PhysicsManager* mInstance;
		PhysicsImplementation* mImpl = nullptr; //private implementation

	public:
		static PhysicsManager* getInstance() {
			PTSD_ASSERT(mInstance != nullptr,"PhysicsManager accessed before init");
			return mInstance;
		}

		static void init();
		void update();
		void shutdown();

		PhysicsManager() = default;
		~PhysicsManager() = default;
	};
}