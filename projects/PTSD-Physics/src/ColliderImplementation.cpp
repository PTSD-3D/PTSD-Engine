#include "PhysicsImplementation.h"
#include "ColliderImplementation.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

namespace PTSD {
	ColliderImplementation::ColliderImplementation() {
		mWorld = PhysicsImplementation::getInstance()->getWorld();
		mObj = nullptr;
	}

	btCollisionObject* ColliderImplementation::addSphereCollider(float size) {
		mObj = new btCollisionObject();
		btCollisionShape* shape = new btSphereShape(size);
		mObj->setCollisionShape(shape);
		mWorld->addCollisionObject(mObj);
		return mObj;
	}
	btCollisionObject* ColliderImplementation::addBoxCollider(Vec3Placeholder size) {
		mObj = new btCollisionObject();
		btCollisionShape* shape = new btBoxShape(btVector3(size.x, size.y, size.z));
		mObj->setCollisionShape(shape);
		mWorld->addCollisionObject(mObj);
		return mObj;
	}

	Vec3Placeholder ColliderImplementation::getTransformOrigin() {
		btVector3 t = mObj->getWorldTransform().getOrigin();
		return { (float)t.x(), (float)t.y(), (float)t.z() };
	}
}