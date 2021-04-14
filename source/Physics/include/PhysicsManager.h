#pragma once
#include "PTSDVectors.h"
#include <assert.h>

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class btCollisionObject;

namespace PTSD {

	class Rigidbody;
	class Collider;

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
			assert(mInstance != nullptr);
			return mInstance;
		}

		void init();
		void update();
		void shutdown();

		btBroadphaseInterface* getBroadphase() const { return mBroadphase; }
		btDefaultCollisionConfiguration* getCollisionConfiguration() const { return mCollisionConfiguration; }
		btCollisionDispatcher* getDispatcher() const { return mDispatcher; }
		btSequentialImpulseConstraintSolver* getSolver() const { return mSolver; }
		btDiscreteDynamicsWorld* getWorld() const { return mWorld; }

		Rigidbody *addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		Rigidbody* addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });

		Collider* addSphereCollider(float size);
		Collider* addBoxCollider(Vec3Placeholder size);

		PhysicsManager() { mInstance = this; }
		~PhysicsManager() = default;
	};
}