#pragma once

#include <memory>
#include "PTSDVectors.h"

class btRigidBody;

namespace PTSD
{
	class RigidbodyImplementation;
	class Rigidbody {
	private:
		std::unique_ptr<RigidbodyImplementation> mImplementation;//private implementation w Bullet
		btRigidBody* mObj;
		Rigidbody();
		~Rigidbody() = default;
	public:
		Rigidbody* addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		Rigidbody* addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		void addForce(Vec3Placeholder force, Vec3Placeholder ref = { 0,0,0 });
	};
}