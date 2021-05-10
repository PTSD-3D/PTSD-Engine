#include "PhysicsManager.h"
#include <string>
#include <BtOgre.h>
#include <Ogre.h>
#include "LogManager.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "ScriptManager.h"
namespace PTSD {

	PhysicsManager* PhysicsManager::mInstance = nullptr;

	void PhysicsManager::init() {
		PTSD_ASSERT(mInstance == nullptr, "PhysicsManager already initialized");
		mInstance = new PhysicsManager();
		
		mInstance->mCollisionConfiguration = new btDefaultCollisionConfiguration();

		mInstance->mDispatcher = new btCollisionDispatcher(mInstance->mCollisionConfiguration);

		mInstance->mBroadphase = new btDbvtBroadphase();

		mInstance->mSolver = new btSequentialImpulseConstraintSolver;
		auto world = new BtOgre::DynamicsWorld(Ogre::Vector3(0,0,0));
		mInstance->mWorld = static_cast<btDiscreteDynamicsWorld*>(world-> getBtWorld());//new btDiscreteDynamicsWorld(mInstance->mDispatcher, mInstance->mBroadphase, mInstance->mSolver, mInstance->mCollisionConfiguration);
		// mInstance->mWorld = new btDiscreteDynamicsWorld(mInstance->mDispatcher, mInstance->mBroadphase, mInstance->mSolver, mInstance->mCollisionConfiguration);
		std::function<void(unsigned long,unsigned long, const btManifoldPoint&)> listener=[&](PTSD::UUID a,PTSD::UUID b, const btManifoldPoint& manifold){
			mInstance->mScriptManager->sendCollisionEvent(a,b,manifold);
		};
		mInstance->mCollisionListener = new BtOgre::CollisionListener(listener);
	}

	void PhysicsManager::update(const float& deltaTime) {
		//generic deltaTime
		mWorld->stepSimulation((deltaTime));
		// BtOgre::onTick(mWorld, deltaTime);
		//logActivity();
	}

	void PhysicsManager::shutdown() {
		delete mCollisionConfiguration;
		delete mDispatcher;
		delete mBroadphase;
		delete mSolver;
		delete mWorld;
	}

	void PhysicsManager::setGravity(float grav)
	{
		mWorld->setGravity(btVector3(0, grav, 0)); //3 dimensional gravity should not be needed. Could be changed easily.
	}


	//for debugging purposes, not meant to be in the final engine
	void PhysicsManager::logActivity() {
		// print positions of all objects
		for (int j = mWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = mWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);
			}
			else
			{
				trans = obj->getWorldTransform();
			}
			std::string s = "World pos object " + std::to_string(j) + " = " + std::to_string(float(trans.getOrigin().getX())) + ", " +
				std::to_string(float(trans.getOrigin().getY())) + ", " + std::to_string(float(trans.getOrigin().getZ())) + "\n";
			//LOG(s.c_str(), Trace);
		}
	}

	btRigidBody* PhysicsManager::addRigidBody(Vec3 size, float mass, Vec3 pos, Vec3 rot) {
		btCollisionShape* shape = nullptr;
		if (size.y == 0.0f && size.z == 0.0f)
			shape = new btSphereShape(size.x);
		else shape = new btBoxShape(btVector3(size.x, size.y, size.z));
		btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(rot.x, rot.y, rot.z), btVector3(pos.x, pos.y, pos.z)));
		btRigidBody* mObj = new btRigidBody(mass, state, shape);
		mWorld->addRigidBody(mObj);
		return mObj;
	}
	void PhysicsManager::setCollisionFlags(btRigidBody* rb, CollisionFlags type, bool trigger) {
		if (trigger) rb->setCollisionFlags(type | CollisionFlags::Trigger);
		else rb->setCollisionFlags(type);
	}
}