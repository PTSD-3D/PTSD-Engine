#pragma once
#include "PTSDVectors.h"

class btDiscreteDynamicsWorld;
class btRigidBody;

namespace PTSD {
	class RigidbodyImplementation {
	private:
		btDiscreteDynamicsWorld* mWorld;
		btRigidBody* mObj;
	public:
		RigidbodyImplementation();
		~RigidbodyImplementation() = default;
		btRigidBody* addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		btRigidBody* addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		void addForce(Vec3Placeholder force, Vec3Placeholder ref = { 0,0,0 });
	};
}
