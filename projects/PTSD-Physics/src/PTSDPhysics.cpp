#include "PTSDPhysics.h"

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

		return 0;
	}
}