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
		void setLinearVelocity(Vec3Placeholder vel);
		void setAngularVelocity(Vec3Placeholder vel);
		void addForce(Vec3Placeholder force, Vec3Placeholder ref = { 0,0,0 });
		btRigidBody* getObj() { return mObj; }
		Rigidbody(btRigidBody* mObj);
		~Rigidbody() = default;
	};
}