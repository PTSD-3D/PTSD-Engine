#include "RigidbodyComponent.h"
#include "PhysicsManager.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BtOgre.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace PTSD
{
	RigidbodyComponent::RigidbodyComponent(Vec3 size, float mass, Vec3 pos, CollisionFlags type, bool trigger, Vec3 rot) : 
		Component(CmpId::RigidbodyC), trigger(trigger), mass(mass), type(type) {
		mObj = PhysicsManager::getInstance()->addRigidBody(size, (type!=CollisionFlags::Static) ? mass : 0, pos,&mColShape, degToRad(rot));
		if (mColShape != nullptr)
			LOG("CollisionShape assigned on Pimpl", Info);
		PhysicsManager::getInstance()->setCollisionFlags(mObj, type, trigger);
	}

	RigidbodyComponent::~RigidbodyComponent()
	{
		//LOG("deleting rb");
		//PhysicsManager::getInstance()->removeRigidBody(mObj);
	}

	void RigidbodyComponent::init() {
		rbState = new BtOgre::RigidBodyState(entity_->getComponent<TransformComponent>(CmpId::Transform)->getNode());
		mObj->setMotionState(rbState);
		mObj->setUserPointer((void*)(new BtOgre::EntityCollisionListener(PhysicsManager::getInstance()->getCollisionListener(), entity_->getID())));
	}

	void RigidbodyComponent::disable()
	{
		PhysicsManager::getInstance()->removeCollision(mObj);
	}

	void RigidbodyComponent::setLinearVelocity(Vec3 vel) {
		mObj->setLinearVelocity(btVector3(vel.x, vel.y, vel.z));
	}

	void RigidbodyComponent::setAngularVelocity(Vec3 vel) {
		mObj->setAngularVelocity(btVector3(vel.x, vel.y, vel.z));
	}

	void RigidbodyComponent::addForce(Vec3 force, Vec3 ref) {
		mObj->applyForce(btVector3(force.x, force.y, force.z), btVector3(ref.x, ref.y, ref.z));
	}

	bool RigidbodyComponent::hasRayCastHit(Vec3 vec) {
		//How raycast works: World->rayTest(origin point, destination point, callback)
		//The callback has the information of the raycast (if it hit, how many hits, etc)
		btVector3 origin = mObj->getWorldTransform().getOrigin();
		btVector3 dest = origin + btVector3(vec.x, vec.y, vec.z);
		btCollisionWorld::ClosestRayResultCallback rayCallback(origin, dest);
		PhysicsManager::getInstance()->getWorld()->rayTest(origin, dest, rayCallback);
		if (rayCallback.hasHit()) return true;
		return false;
  }
	void RigidbodyComponent::setPosition(Vec3 position)
	{
		btTransform transform = mObj->getCenterOfMassTransform();
		transform.setOrigin(btVector3(position.x,position.y,position.z));
		mObj->setCenterOfMassTransform(transform);
	}

	Vec3 RigidbodyComponent::getLinearVelocity() {
		btVector3 v = mObj->getLinearVelocity();
		return Vec3(v.getX(), v.getY(), v.getZ());
	}

	Vec3 RigidbodyComponent::getAngularVelocity() {
		btVector3 v = mObj->getAngularVelocity();
		return Vec3(v.getX(), v.getY(), v.getZ());
	}

	Vec3 RigidbodyComponent::getPos() {
		btVector3 p = mObj->getWorldTransform().getOrigin();
		return Vec3(p.getX(), p.getY(), p.getZ());
	}

	Vec4Placeholder RigidbodyComponent::getRot() {
		btQuaternion r = mObj->getWorldTransform().getRotation();
		return Vec4Placeholder(r.getX(), r.getY(), r.getZ(), r.getW());
	}

	void RigidbodyComponent::setCollisionScale(Vec3 sc)
	{
		if (mColShape != nullptr) {
			mColShape->setLocalScaling({ sc.x,sc.y,sc.z });
			PhysicsManager::getInstance()->getWorld()->getCollisionWorld()->updateSingleAabb(mObj);
		}
		else
			LOG("Collision shape was null", Error);
	}
}
