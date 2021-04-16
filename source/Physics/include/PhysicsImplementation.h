#pragma once
#include "PTSDVectors.h"

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class btCollisionObject;

namespace PTSD {
	class PhysicsImplementation {
	private:
		btBroadphaseInterface* mBroadphase;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;
		btDiscreteDynamicsWorld* mWorld;

		void testScene();
		void logActivity();

		PhysicsImplementation() = default;
		static PhysicsImplementation* mInstance;

	public:
		static PhysicsImplementation* getInstance() {
			if (mInstance == nullptr)
				mInstance = new PhysicsImplementation();
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

		~PhysicsImplementation() = default;
	};
}
