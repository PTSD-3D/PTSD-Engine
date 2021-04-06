#pragma once

#include <memory>
#include "PTSDVectors.h"

class btCollisionObject;

namespace PTSD
{
	class ColliderImplementation;
	class Collider {
	private:
		std::unique_ptr<ColliderImplementation> mImplementation;//private implementation w Bullet
		btCollisionObject* mObj;
		Collider();
		~Collider() = default;
	public:
		Collider* addSphereCollider(float size);
		Collider* addBoxCollider(Vec3Placeholder size);
		Vec3Placeholder getTransformOrigin();
	};
}