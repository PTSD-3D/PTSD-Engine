#pragma once

#include <memory>
#include "PTSDVectors.h"
#include "Component.h"

class btRigidBody;
namespace BtOgre {
	class RigidBodyState;
}


namespace PTSD
{
	enum CollisionFlags {
		Dynamic, Static, Kinematic, Trigger = 4
	};

	class Rigidbody: public Component {
	private:
		btRigidBody* mObj = nullptr;
		BtOgre::RigidBodyState* rbState = nullptr;

		void initRB(CollisionFlags type, bool trigger);
	public:
		Rigidbody(Vec3Placeholder size, float mass, Vec3Placeholder pos, CollisionFlags type = CollisionFlags::Dynamic, bool trigger = false, Vec4Placeholder quat = { 0,0,0,1 });
		~Rigidbody() = default;

		void setLinearVelocity(Vec3Placeholder vel);
		void setAngularVelocity(Vec3Placeholder vel);
		void addForce(Vec3Placeholder force, Vec3Placeholder ref = { 0,0,0 });

		Vec3Placeholder getLinearVelocity();
		Vec3Placeholder getAngularVelocity();
	};
}