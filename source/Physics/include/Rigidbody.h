#pragma once

#include <memory>
#include "PTSDVectors.h"

class btRigidBody;

namespace PTSD
{
	class Rigidbody {
	private:
		btRigidBody* mObj;
	public:
		Rigidbody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		Rigidbody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		~Rigidbody() = default;

		void setLinearVelocity(Vec3Placeholder vel);
		void setAngularVelocity(Vec3Placeholder vel);
		void addForce(Vec3Placeholder force, Vec3Placeholder ref = { 0,0,0 });
	};
}