#include "PTSDPhysics.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#define BT_USE_DOUBLE_PRECISION = 1

namespace PTSD {

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
		dynamicsWorld->addCollisionObject(new btCollisionObject());

		for (int i = 0; i < 100; i++)
		{
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
				printf(" world pos object %d = %f ,%f ,%f\n", j, float(trans.getOrigin().getX()), float(
					trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
			}
		}

		return 0;
	}
}