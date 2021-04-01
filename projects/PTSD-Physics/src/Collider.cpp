#include "Collider.h"
#include "ColliderImplementation.h"

PTSD::Collider::Collider() {
	mImplementation = std::make_unique<ColliderImplementation>();
}

PTSD::Collider* PTSD::Collider::addSphereCollider(float size) {
	Collider* col = new Collider();
	mObj = mImplementation->addSphereCollider(size);
	return col;
}

PTSD::Collider* PTSD::Collider::addBoxCollider(Vec3Placeholder size) {
	Collider* col = new Collider();
	mObj = mImplementation->addBoxCollider(size);
	return col;
}

Vec3Placeholder PTSD::Collider::getTransformOrigin() {
	return mImplementation->getTransformOrigin();
}

