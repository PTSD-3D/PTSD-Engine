#pragma once

#include <memory>
#include "PTSDVectors.h"
#include "Component.h"
#include <SDL_stdinc.h>

class btRigidBody;
namespace BtOgre {
	class RigidBodyState;
}


namespace PTSD
{
	enum CollisionFlags {
		Dynamic, Static, Kinematic, Trigger = 4
	};

	class RigidbodyComponent: public Component {
	private:
		btRigidBody* mObj = nullptr;
		BtOgre::RigidBodyState* rbState = nullptr;
		CollisionFlags type;
		bool trigger;
		float mass;
		Vec3 degToRad(Vec3 deg) {
			return { deg.x * 180 / (float)M_PI, deg.y * 180 / (float)M_PI, deg.z * 180 / (float)M_PI };
		}
	public:
		RigidbodyComponent(Vec3 size, float mass, Vec3 pos, CollisionFlags type = CollisionFlags::Dynamic, bool trigger = false, Vec3 rot = { 0,0,0 });
		virtual ~RigidbodyComponent();

		virtual void init();
		virtual void disable() override;

		void setLinearVelocity(Vec3 vel);
		void setAngularVelocity(Vec3 vel);
		void addForce(Vec3 force, Vec3 ref = { 0,0,0 });
		void setPosition(Vec3 position);

		CollisionFlags getType() { return type; }
		bool isTrigger() { return trigger; }
		float getMass() { return mass; }
		Vec3 getLinearVelocity();
		Vec3 getAngularVelocity();
		Vec3 getPos();
		Vec4Placeholder getRot();		
	};
}