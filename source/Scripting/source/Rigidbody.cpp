#include "Rigidbody.h"
#include "PhysicsManager.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BtOgre.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace PTSD
{

	Rigidbody::Rigidbody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) : Component(CmpId::RigidbodyC) {
		mObj = PhysicsManager::getInstance()->addSphereRigidBody(size, mass, pos, quat);
	}

	Rigidbody::Rigidbody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) : Component(CmpId::RigidbodyC) {
		mObj = PhysicsManager::getInstance()->addBoxRigidBody(size, mass, pos, quat);
	}

	void Rigidbody::init() {
		rbState = new BtOgre::RigidBodyState(entity_->getComponent<TransformComponent>(CmpId::Transform)->getNode());
		mObj->setMotionState(rbState);
	}

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
