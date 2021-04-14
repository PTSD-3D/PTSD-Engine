#pragma once

#include <memory>
#include "PTSDVectors.h"

class btRigidBody;

namespace PTSD
{
	class RigidbodyImplementation;
	class Rigidbody {
	private:
		btDiscreteDynamicsWorld* mWorld;
		btRigidBody* mObj;
	public:
		Rigidbody* addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		Rigidbody* addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		void addForce(Vec3Placeholder force, Vec3Placeholder ref = { 0,0,0 });
		Rigidbody();
		~Rigidbody() = default;
	};
}