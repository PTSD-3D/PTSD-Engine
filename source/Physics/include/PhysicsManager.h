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
class btGhostObject;
namespace BtOgre{
struct CollisionListener;
struct EntityCollisionListener;
}

namespace PTSD {
	class ScriptManager;
	class PhysicsManager
	{
	private:
		static PhysicsManager* mInstance;
		ScriptManager * mScriptManager;

		btBroadphaseInterface* mBroadphase;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;
		btDiscreteDynamicsWorld* mWorld;
		BtOgre::CollisionListener* mCollisionListener;
		void logActivity();
	public:
		void setScriptManager(ScriptManager* sm) {mScriptManager = sm;}
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
		BtOgre::CollisionListener* getCollisionListener() const {return mCollisionListener;}

		btRigidBody* addRigidBody(Vec3 size, float mass, Vec3 pos,btCollisionShape** shape, Vec3 rot = { 0,0,0 });

		void removeCollision(btRigidBody* body);
		void removeRigidBody(btRigidBody* body);

		void setCollisionFlags(btRigidBody* rb, CollisionFlags type, bool trigger);

		PhysicsManager() { mInstance = this; }
		~PhysicsManager() = default;
	};
}