#include "PTSDPhysics.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

namespace PTSD {

	//Test code.
	//Creates a physics world and prints out the position of an object.
	int PTSDPhysics::init() {

		btDefaultCollisionConfiguration* collisionConfiguration = new
			btDefaultCollisionConfiguration();

		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

		btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

		btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
			overlappingPairCache, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0, -10, 0));
		btCollisionObject* obj = new btCollisionObject();
		btCollisionShape* shape = new btSphereShape(5);

		obj->setCollisionShape(shape);
		dynamicsWorld->addCollisionObject(obj);

		dynamicsWorld->stepSimulation(1.0 / 60, 10);

		// print positions of all objects
		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
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
	
		return 0;
	}
}