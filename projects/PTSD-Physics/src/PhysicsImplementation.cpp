#pragma once
#include "PTSDLog.h"
#include "PhysicsImplementation.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "ColliderImplementation.h" //for demonstration purposes

namespace PTSD {

	PhysicsImplementation* PhysicsImplementation::mInstance = nullptr;

	//example scene
	void PhysicsImplementation::testScene() {
		mWorld->setGravity(btVector3(0, -10, 0));

		ColliderImplementation* col = new ColliderImplementation();

		btCollisionObject* obj = col->addSphereCollider(5);

		btCollisionObject* obj2 = col->addBoxCollider({ 5,5,5 });
		btRigidBody* body = addBoxRigidBody({ 5,5,5 }, 1, { 0,100,0 });
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
			printf(" world pos object %d = %f ,%f ,%f\n", j, float(trans.getOrigin().getX()), float(
				trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}
	}

	btRigidBody* PhysicsImplementation::addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) {
		btCollisionShape* shape = new btBoxShape(btVector3(size.x, size.y, size.z));
		btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(quat.x, quat.y, quat.z, quat.w), btVector3(pos.x, pos.y, pos.z)));
		btRigidBody* body = new btRigidBody(mass, state, shape);
		mWorld->addRigidBody(body);
		return body;
	}

	btRigidBody* PhysicsImplementation::addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat) {
		btCollisionShape* shape = new btSphereShape(size);
		btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(quat.x, quat.y, quat.z, quat.w), btVector3(pos.x, pos.y, pos.z)));
		btRigidBody* body = new btRigidBody(mass, state, shape);
		mWorld->addRigidBody(body);
		return body;
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