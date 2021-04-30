#pragma once
#include "PTSDVectors.h"
#include "PTSDAssert.h"
#include "RigidbodyComponent.h"

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;

namespace PTSD {
	class PhysicsManager
	{
	private:
		static PhysicsManager* mInstance;

		btBroadphaseInterface* mBroadphase;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;
		btDiscreteDynamicsWorld* mWorld;

		void testScene();
		void logActivity();
	public:
		static PhysicsManager* getInstance() {
			PTSD_ASSERT(mInstance != nullptr,"PhysicsManager not initialized");
			return mInstance;
		}

		static void init();
		void update(const float& deltaTime);
		void shutdown();

		void setGravity(float grav);

		btBroadphaseInterface* getBroadphase() const { return mBroadphase; }
		btDefaultCollisionConfiguration* getCollisionConfiguration() const { return mCollisionConfiguration; }
		btCollisionDispatcher* getDispatcher() const { return mDispatcher; }
		btSequentialImpulseConstraintSolver* getSolver() const { return mSolver; }
		btDiscreteDynamicsWorld* getWorld() const { return mWorld; }

		btRigidBody* addRigidBody(Vec3 size, float mass, Vec3 pos, Vec3 rot = { 0,0,0 });

		void setCollisionFlags(btRigidBody* rb, CollisionFlags type, bool trigger);

		PhysicsManager() { mInstance = this; }
		~PhysicsManager() = default;
	};
}