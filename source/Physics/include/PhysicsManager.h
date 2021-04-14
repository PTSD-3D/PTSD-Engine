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
	class PhysicsImplementation;

	class PhysicsManager
	{
	private:
		static PhysicsManager* mInstance;
		PhysicsImplementation* mImpl = nullptr; //private implementation

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

		PhysicsManager() { mInstance = this; }
		~PhysicsManager() = default;
	};
}