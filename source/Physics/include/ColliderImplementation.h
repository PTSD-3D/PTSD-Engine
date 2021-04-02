#pragma once
#include "PTSDVectors.h"

class btDiscreteDynamicsWorld;
class btCollisionObject;

namespace PTSD {
	class ColliderImplementation {
	private:
		btDiscreteDynamicsWorld* mWorld;	
		btCollisionObject* mObj;
	public:
		ColliderImplementation();
		~ColliderImplementation() = default;
		btCollisionObject* addSphereCollider(float size);
		btCollisionObject* addBoxCollider(Vec3Placeholder size);
		Vec3Placeholder getTransformOrigin();
	};
}
