#pragma once

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

namespace PTSD {
	class PhysicsImpl {
	private:
		btBroadphaseInterface* mBroadphase;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;
		btDiscreteDynamicsWorld* mWorld;

		void testScene();
		void logActivity();

		PhysicsImpl() = default;
		static PhysicsImpl* mInstance;

	public:
		static PhysicsImpl* getInstance() {
			if (mInstance == nullptr)
				mInstance = new PhysicsImpl();
			return mInstance;;
		}
		void Init();
		void Update();
		void Shutdown();

		btBroadphaseInterface* getBroadphase() const { return mBroadphase; }
		btDefaultCollisionConfiguration* getCollisionConfiguration() const { return mCollisionConfiguration; }
		btCollisionDispatcher* getDispatcher() const { return mDispatcher; }
		btSequentialImpulseConstraintSolver* getSolver() const { return mSolver; }
		btDiscreteDynamicsWorld* getWorld() const { return mWorld; }

		~PhysicsImpl() = default;
	};
}
