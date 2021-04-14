#pragma once

#include <memory>
#include "PTSDVectors.h"

class btCollisionObject;
class btDiscreteDynamicsWorld;

namespace PTSD
{
	class ColliderImplementation;
	class Collider {
	private:
		btDiscreteDynamicsWorld* mWorld;
		btCollisionObject* mObj;
		
	public:
		Collider* addSphereCollider(float size);
		Collider* addBoxCollider(Vec3Placeholder size);
		Vec3Placeholder getTransformOrigin();
		btCollisionObject* getObj() { return mObj; }
		Collider();
		~Collider() = default;
	};
}