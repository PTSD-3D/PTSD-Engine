#include "Collider.h"
#include "PhysicsManager.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

PTSD::Collider::Collider(btCollisionObject* mObj) : mObj(mObj) {}

Vec3Placeholder PTSD::Collider::getTransformOrigin() {
	btVector3 t = mObj->getWorldTransform().getOrigin();
	return { (float)t.x(), (float)t.y(), (float)t.z() };
}

