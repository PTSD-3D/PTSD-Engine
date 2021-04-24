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
	class Rigidbody: public Component {
	private:
		btRigidBody* mObj = nullptr;
		BtOgre::RigidBodyState* rbState = nullptr;
	public:
		Rigidbody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		Rigidbody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		~Rigidbody() = default;

		virtual void init();

		void setLinearVelocity(Vec3Placeholder vel);
		void setAngularVelocity(Vec3Placeholder vel);
		void addForce(Vec3Placeholder force, Vec3Placeholder ref = { 0,0,0 });
	};
}