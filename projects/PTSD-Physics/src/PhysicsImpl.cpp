#pragma once
#include "PhysicsImpl.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

namespace PTSD {

	PhysicsImpl* PhysicsImpl::mInstance = nullptr;

	void PhysicsImpl::testScene() {
		mWorld->setGravity(btVector3(0, -10, 0));
		btCollisionObject* obj = new btCollisionObject();
		btCollisionShape* shape = new btSphereShape(5);

		obj->setCollisionShape(shape);
		mWorld->addCollisionObject(obj);

		btCollisionObject* obj2 = new btCollisionObject();
		btCollisionShape* shape2 = new btSphereShape(10);
		btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(),btVector3(0,100,0)));
		btRigidBody* body = new btRigidBody(1, state, shape2);

		obj2->setCollisionShape(shape2);
		mWorld->addCollisionObject(obj2);
		mWorld->addRigidBody(body);
	}

	void PhysicsImpl::logActivity() {
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
			printf("I'm the physics module. I make objects go brrrrr!!!\n");
			printf(" world pos object %d = %f ,%f ,%f\n", j, float(trans.getOrigin().getX()), float(
				trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}
	}

	void PhysicsImpl::Init() {
		mCollisionConfiguration = new btDefaultCollisionConfiguration();

		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

		mBroadphase = new btDbvtBroadphase();

		mSolver = new btSequentialImpulseConstraintSolver;

		mWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);

		testScene();
	}

	void PhysicsImpl::Update() {
		//deltaTime genérico
		mWorld->stepSimulation((1.0 / 60, 10));
		logActivity();
	}

	void PhysicsImpl::Shutdown() {
		delete mCollisionConfiguration;
		delete mDispatcher;
		delete mBroadphase;
		delete mSolver;
		delete mWorld;
	}
}