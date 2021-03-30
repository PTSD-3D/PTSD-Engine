#include "PTSDPhysics.h"
#include "PhysicsImpl.h"

namespace PTSD {

	Physics* Physics::mInstance = nullptr;

	void Physics::Init() {
		mImpl = PhysicsImpl::getInstance();
		mImpl->Init();
	}

	void Physics::Update() {
		mImpl->Update();
	}

	void Physics::Shutdown() {
		mImpl->Shutdown();
	}
}