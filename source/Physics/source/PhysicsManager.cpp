#include "PhysicsManager.h"
#include <string>
#include "LogManager.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "Collider.h" //for demonstration purposes
#include "Rigidbody.h" //for demonstration purposes

namespace PTSD {

	PhysicsManager* PhysicsManager::mInstance = nullptr;

	void PhysicsManager::init() {
		PTSD_ASSERT(mInstance == nullptr, "PhysicsManager already initialized");
		mInstance = new PhysicsManager();
		
		mInstance->mCollisionConfiguration = new btDefaultCollisionConfiguration();

		mInstance->mDispatcher = new btCollisionDispatcher(mInstance->mCollisionConfiguration);

		mInstance->mBroadphase = new btDbvtBroadphase();

		mInstance->mSolver = new btSequentialImpulseConstraintSolver;

		mInstance->mWorld = new btDiscreteDynamicsWorld(mInstance->mDispatcher, mInstance->mBroadphase, mInstance->mSolver, mInstance->mCollisionConfiguration);

		mInstance->testScene();
	}

	void PhysicsManager::update(const float& deltaTime) {
		//generic deltaTime
		mWorld->stepSimulation((deltaTime));
		logActivity();
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

	//example scene
	void PhysicsManager::testScene() {
		mWorld->setGravity(btVector3(0, -10, 0));

		Rigidbody* rig = new Rigidbody({ 5,5,5 }, 1, { 0,100,0 });

		Collider* col = new Collider(5);

		Collider* col2 = new Collider({ 5,5,5 });

		rig->addForce({ 10,0,0 });
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

	btRigidBody* PhysicsManager::addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) {
		btCollisionShape* shape = new btSphereShape(size);
		btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(quat.x, quat.y, quat.z, quat.w), btVector3(pos.x, pos.y, pos.z)));
		btRigidBody* mObj = new btRigidBody(mass, state, shape);
		mWorld->addRigidBody(mObj);
		return mObj;
	}

	btRigidBody* PhysicsManager::addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) {
		btCollisionShape* shape = new btBoxShape(btVector3(size.x, size.y, size.z));
		btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(quat.x, quat.y, quat.z, quat.w), btVector3(pos.x, pos.y, pos.z)));
		btRigidBody* mObj = new btRigidBody(mass, state, shape);
		mWorld->addRigidBody(mObj);
		return mObj;
	}

	btCollisionObject* PhysicsManager::addSphereCollider(float size) {
		btCollisionObject* mObj = new btCollisionObject();
		btCollisionShape* shape = new btSphereShape(size);
		mObj->setCollisionShape(shape);
		mWorld->addCollisionObject(mObj);
		return mObj;
	}

	btCollisionObject* PhysicsManager::addBoxCollider(Vec3Placeholder size) {
		btCollisionObject* mObj = new btCollisionObject();
		btCollisionShape* shape = new btBoxShape(btVector3(size.x, size.y, size.z));
		mObj->setCollisionShape(shape);
		mWorld->addCollisionObject(mObj);
		return mObj;
	}
}