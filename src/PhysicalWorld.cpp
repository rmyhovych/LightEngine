#include "PhysicalWorld.h"

PhysicalWorld::PhysicalWorld(const btVector3& gravity) :
	dynamicsWorld(nullptr)
{
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(gravity);
}

PhysicalWorld::~PhysicalWorld()
{
	//remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}


	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
		objects[i] = nullptr;
	}

	//delete dynamics world
	delete dynamicsWorld;
	dynamicsWorld = nullptr;

	//delete solver
	delete solver;
	solver = nullptr;

	//delete broadphase
	delete overlappingPairCache;
	overlappingPairCache = nullptr;

	//delete dispatcher
	delete dispatcher;
	dispatcher = nullptr;

	delete collisionConfiguration;
	collisionConfiguration = nullptr;
}



void PhysicalWorld::linkSphere(Object* object, const PhysicalObject::Properties& properties)
{
	PhysicalObject* pO = new PhysicalObjectSphere(object, properties);

	objects.push_back(pO);

	dynamicsWorld->addRigidBody(pO->getBody());
}

void PhysicalWorld::linkPrism(Object* object, const PhysicalObject::Properties& properties)
{
	PhysicalObject* pO = new PhysicalObjectPrism(object, properties);

	objects.push_back(pO);

	dynamicsWorld->addRigidBody(pO->getBody());
}




void PhysicalWorld::step(double fps)
{
	dynamicsWorld->stepSimulation(1.0 / fps, 10);

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->act();
	}
}
