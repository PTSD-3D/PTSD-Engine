#include "Rigidbody.h"
#include "RigidbodyImplementation.h"

namespace PTSD
{


	Rigidbody::Rigidbody() {
		mImplementation = std::make_unique<RigidbodyImplementation>();
	}

	Rigidbody* PTSD::Rigidbody::addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) {
		Rigidbody* rig = new Rigidbody();
		mObj = mImplementation->addSphereRigidBody(size, mass, pos, quat);
		return rig;
	}

	Rigidbody* PTSD::Rigidbody::addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) {
		Rigidbody* rig = new Rigidbody();
		mObj = mImplementation->addBoxRigidBody(size, mass, pos, quat);
		return rig;
	}

	void Rigidbody::addForce(Vec3Placeholder force, Vec3Placeholder ref) {
		mImplementation->addForce(force, ref);
	}
}
