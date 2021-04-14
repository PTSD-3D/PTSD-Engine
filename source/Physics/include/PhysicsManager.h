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
		void update(const float& deltaTime);
		void shutdown();

		btBroadphaseInterface* getBroadphase() const { return mBroadphase; }
		btDefaultCollisionConfiguration* getCollisionConfiguration() const { return mCollisionConfiguration; }
		btCollisionDispatcher* getDispatcher() const { return mDispatcher; }
		btSequentialImpulseConstraintSolver* getSolver() const { return mSolver; }
		btDiscreteDynamicsWorld* getWorld() const { return mWorld; }

		btRigidBody *addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		btRigidBody* addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });

		btCollisionObject* addSphereCollider(float size);
		btCollisionObject* addBoxCollider(Vec3Placeholder size);

		PhysicsManager() { mInstance = this; }
		~PhysicsManager() = default;
	};
}