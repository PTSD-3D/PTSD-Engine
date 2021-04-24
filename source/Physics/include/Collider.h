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
		Collider(float size);
		Collider(Vec3Placeholder size);
		~Collider() = default;

		Vec3Placeholder getTransformOrigin();		
	};
}