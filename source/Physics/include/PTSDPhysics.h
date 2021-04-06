#pragma once

namespace PTSD {
	class PhysicsImplementation;

	class Physics
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