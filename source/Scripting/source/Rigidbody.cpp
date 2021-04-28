#include "Rigidbody.h"
#include "PhysicsManager.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BtOgre.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace PTSD
{
	Rigidbody::Rigidbody(Vec3Placeholder size, float mass, Vec3Placeholder pos, CollisionFlags type, bool trigger, Vec4Placeholder quat) : 
		Component(CmpId::RigidbodyC), trigger(trigger), mass(mass), type(type) {
		mObj = PhysicsManager::getInstance()->addRigidBody(size, mass, pos, quat);
		PhysicsManager::getInstance()->setCollisionFlags(mObj, type, trigger);
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

	Vec3Placeholder Rigidbody::getLinearVelocity() {
		btVector3 v = mObj->getLinearVelocity();
		return Vec3Placeholder(v.getX(), v.getY(), v.getZ());
	}

	Vec3Placeholder Rigidbody::getAngularVelocity() {
		btVector3 v = mObj->getAngularVelocity();
		return Vec3Placeholder(v.getX(), v.getY(), v.getZ());
	}

	Vec3Placeholder Rigidbody::getPos() {
		btVector3 p = mObj->getWorldTransform().getOrigin();
		return Vec3Placeholder(p.getX(), p.getY(), p.getZ());
	}

	Vec4Placeholder Rigidbody::getRot() {
		btQuaternion r = mObj->getWorldTransform().getRotation();
		return Vec4Placeholder(r.getX(), r.getY(), r.getZ(), r.getW());
	}
}
