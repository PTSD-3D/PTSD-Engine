#include "PhysicsManager.h"
#include "PhysicsImplementation.h"

namespace PTSD {

	PhysicsManager* PhysicsManager::mInstance = nullptr;

	void PhysicsManager::init() {
		PTSD_ASSERT(mInstance == nullptr, "PhysicsManager already initialized");
		mInstance = new PhysicsManager();
		mInstance->mImpl = PhysicsImplementation::getInstance();
		mInstance->mImpl->init();
	}

	void PhysicsManager::update() {
		mImpl->update();
	}

	void PhysicsManager::shutdown() {
		mImpl->shutdown();
	}
}