#include "Rigidbody.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

namespace PTSD
{
	Rigidbody::Rigidbody(btRigidBody* mObj) : mObj(mObj) {}

	void Rigidbody::setLinearVelocity(Vec3Placeholder vel) {
		mObj->setLinearVelocity(btVector3(vel.x, vel.y, vel.z));
	}

	void Rigidbody::setAngularVelocity(Vec3Placeholder vel) {
		mObj->setAngularVelocity(btVector3(vel.x, vel.y, vel.z));
	}

	void Rigidbody::addForce(Vec3Placeholder force, Vec3Placeholder ref) {
		mObj->applyForce(btVector3(force.x, force.y, force.z), btVector3(ref.x, ref.y, ref.z));
	}
}
