#include "PhysicsManager.h"
#include <string>
#include "PTSDLog.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "Collider.h" //for demonstration purposes
#include "Rigidbody.h" //for demonstration purposes

namespace PTSD {

	PhysicsManager* PhysicsManager::mInstance = nullptr;

	void PhysicsManager::init() {
		mCollisionConfiguration = new btDefaultCollisionConfiguration();

		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

		mBroadphase = new btDbvtBroadphase();

		mSolver = new btSequentialImpulseConstraintSolver;

		mWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);

		testScene();
	}

	void PhysicsManager::update() {
		//generic deltaTime
		mWorld->stepSimulation((1.0 / 60, 10));
		logActivity();
	}

	void PhysicsManager::shutdown() {
		delete mCollisionConfiguration;
		delete mDispatcher;
		delete mBroadphase;
		delete mSolver;
		delete mWorld;
	}

	//example scene
	void PhysicsManager::testScene() {
		mWorld->setGravity(btVector3(0, -10, 0));

		btCollisionObject* obj = addSphereCollider(5)->getObj();

		btCollisionObject* obj2 = addBoxCollider({ 5,5,5 })->getObj();
		btRigidBody* body = addBoxRigidBody({ 5,5,5 }, 1, { 0,100,0 })->getObj();
		Rigidbody* rig = new Rigidbody(body);

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
			LOG(s.c_str(), Trace);
		}
	}

	Rigidbody* PhysicsManager::addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) {
		btCollisionShape* shape = new btSphereShape(size);
		btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(quat.x, quat.y, quat.z, quat.w), btVector3(pos.x, pos.y, pos.z)));
		btRigidBody* mObj = new btRigidBody(mass, state, shape);
		mWorld->addRigidBody(mObj);
		Rigidbody* rig = new Rigidbody(mObj);
		return rig;
	}

	Rigidbody* PhysicsManager::addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) {
		btCollisionShape* shape = new btBoxShape(btVector3(size.x, size.y, size.z));
		btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(quat.x, quat.y, quat.z, quat.w), btVector3(pos.x, pos.y, pos.z)));
		btRigidBody* mObj = new btRigidBody(mass, state, shape);
		mWorld->addRigidBody(mObj);
		Rigidbody* rig = new Rigidbody(mObj);
		return rig;
	}

	Collider* PhysicsManager::addSphereCollider(float size) {
		btCollisionObject* mObj = new btCollisionObject();
		btCollisionShape* shape = new btSphereShape(size);
		mObj->setCollisionShape(shape);
		mWorld->addCollisionObject(mObj);
		Collider* col = new Collider(mObj);
		return col;
	}

	Collider* PhysicsManager::addBoxCollider(Vec3Placeholder size) {
		btCollisionObject* mObj = new btCollisionObject();
		btCollisionShape* shape = new btBoxShape(btVector3(size.x, size.y, size.z));
		mObj->setCollisionShape(shape);
		mWorld->addCollisionObject(mObj);
		Collider* col = new Collider(mObj);
		return col;
	}
}