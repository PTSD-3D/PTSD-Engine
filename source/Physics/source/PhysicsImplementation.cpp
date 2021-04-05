#pragma once
#include <string>
#include "PTSDLog.h"
#include "PhysicsImplementation.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "ColliderImplementation.h" //for demonstration purposes
#include "RigidbodyImplementation.h" //for demonstration purposes

namespace PTSD {

	PhysicsImplementation* PhysicsImplementation::mInstance = nullptr;

	//example scene
	void PhysicsImplementation::testScene() {
		mWorld->setGravity(btVector3(0, -10, 0));

		ColliderImplementation* col = new ColliderImplementation();
		RigidbodyImplementation* rig = new RigidbodyImplementation();

		btCollisionObject* obj = col->addSphereCollider(5);

		btCollisionObject* obj2 = col->addBoxCollider({ 5,5,5 });
		btRigidBody* body = rig->addBoxRigidBody({ 5,5,5 }, 1, { 0,100,0 });

		rig->addForce({ 10,0,0 });
	}

	//for debugging purposes, not meant to be in the final engine
	void PhysicsImplementation::logActivity() {
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

	void PhysicsImplementation::init() {
		mCollisionConfiguration = new btDefaultCollisionConfiguration();

		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

		mBroadphase = new btDbvtBroadphase();

		mSolver = new btSequentialImpulseConstraintSolver;

		mWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);

		testScene();
	}

	void PhysicsImplementation::update() {
		//generic deltaTime
		mWorld->stepSimulation((1.0 / 60, 10));
		logActivity();
	}

	void PhysicsImplementation::shutdown() {
		delete mCollisionConfiguration;
		delete mDispatcher;
		delete mBroadphase;
		delete mSolver;
		delete mWorld;
	}
}