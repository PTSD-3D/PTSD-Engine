#pragma once
#ifdef _PTSDPHYSICS
#define PHYSICSAPI  __declspec(dllexport)   // export DLL information

#else
#define PHYSICSAPI  __declspec(dllimport)   // import DLL information

#endif

#include <memory>
#include "Vec3.h"

class btCollisionObject;

namespace PTSD
{
	class ColliderImplementation;
	class PHYSICSAPI Collider {
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