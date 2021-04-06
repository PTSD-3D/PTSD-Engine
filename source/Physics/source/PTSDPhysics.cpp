#include "PTSDPhysics.h"
#include "PhysicsImplementation.h"

namespace PTSD {

	Physics* Physics::mInstance = nullptr;

	void Physics::init() {
		mImpl = PhysicsImplementation::getInstance();
		mImpl->init();
	}

	void Physics::update() {
		mImpl->update();
	}

	void Physics::shutdown() {
		mImpl->shutdown();
	}
}