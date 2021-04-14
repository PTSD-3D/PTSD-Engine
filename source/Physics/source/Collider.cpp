#include "Collider.h"
#include "PhysicsManager.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

PTSD::Collider::Collider() {
	mWorld = PhysicsManager::getInstance()->getWorld();
	mObj = nullptr;
}

PTSD::Collider* PTSD::Collider::addSphereCollider(float size) {
	Collider* col = new Collider();
	col->mObj = new btCollisionObject();
	btCollisionShape* shape = new btSphereShape(size);
	col->mObj->setCollisionShape(shape);
	mWorld->addCollisionObject(col->mObj);
	return col;
}

PTSD::Collider* PTSD::Collider::addBoxCollider(Vec3Placeholder size) {
	Collider* col = new Collider();
	col->mObj = new btCollisionObject();
	btCollisionShape* shape = new btBoxShape(btVector3(size.x, size.y, size.z));
	col->mObj->setCollisionShape(shape);
	mWorld->addCollisionObject(col->mObj);
	return col;
}

Vec3Placeholder PTSD::Collider::getTransformOrigin() {
	btVector3 t = mObj->getWorldTransform().getOrigin();
	return { (float)t.x(), (float)t.y(), (float)t.z() };
}

