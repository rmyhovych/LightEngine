#include "PhysicalWorld.h"


PhysicalWorld* PhysicalWorld::getInstance()
{
	static PhysicalWorld physicalWorld({ 0, -10, 0 });

	return &physicalWorld;
}

PhysicalWorld::~PhysicalWorld()
{
	clear();

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



Object* PhysicalWorld::createObject(GraphicalObject* parent, const Object::Properties& properties)
{
	Object* o = new Object(parent, properties);

	properties.m_mass == 0 ? sObjects.push_back(o) : dObjects.push_back(o);

	dynamicsWorld->addRigidBody(o->getBody());

	return o;
}

Object* PhysicalWorld::createObject(GraphicalObject * parent, btEmptyShape* shape)
{
	Object* o = new Object(parent, shape);

	sObjects.push_back(o);

	dynamicsWorld->addRigidBody(o->getBody());

	return o;
}


void PhysicalWorld::step(double fps)
{
	dynamicsWorld->stepSimulation(1.0 / fps, 10);

	for (int i = dObjects.size() - 1; i >= 0; i--)
	{
		dObjects[i]->act();
	}
}

void PhysicalWorld::clear()
{
	//remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			btCollisionShape* shape = body->getCollisionShape();

			delete shape;

			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	for (int i = dObjects.size() - 1; i >= 0; i--)
	{
		delete dObjects[i];
		dObjects[i] = nullptr;
	}

	for (int i = sObjects.size() - 1; i >= 0; i--)
	{
		delete sObjects[i];
		sObjects[i] = nullptr;
	}
}



PhysicalWorld::PhysicalWorld(const btVector3& gravity) :
	dynamicsWorld(nullptr)
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(gravity);
}
