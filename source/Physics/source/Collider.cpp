#include "Collider.h"
#include "PhysicsManager.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

PTSD::Collider::Collider(float size) {
	mObj = PhysicsManager::getInstance()->addSphereCollider(size);
}

PTSD::Collider::Collider(Vec3Placeholder size) {
	mObj = PhysicsManager::getInstance()->addBoxCollider(size);
}

Vec3Placeholder PTSD::Collider::getTransformOrigin() {
	btVector3 t = mObj->getWorldTransform().getOrigin();
	return { (float)t.x(), (float)t.y(), (float)t.z() };
}

