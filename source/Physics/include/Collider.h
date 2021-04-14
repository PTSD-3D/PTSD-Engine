#pragma once

#include <memory>
#include "PTSDVectors.h"

class btCollisionObject;
class btDiscreteDynamicsWorld;

namespace PTSD
{
	class Collider {
	private:
		btCollisionObject* mObj;
	public:
		Vec3Placeholder getTransformOrigin();
		btCollisionObject* getObj() { return mObj; }
		Collider(btCollisionObject* mObj);
		~Collider() = default;
	};
}