#pragma once

#include <btBulletDynamicsCommon.h>

#include "PhysicalObject.h"

class PhysicalWorld
{
public:
	PhysicalWorld(const btVector3& gravity = btVector3(0, -10, 0));
	~PhysicalWorld();

	void addSphere(Object* object);
	void addPrism(Object* object);


	void step(double fps);

private:

	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;

	btDiscreteDynamicsWorld* dynamicsWorld;

	std::vector<PhysicalObject*> objects;
};

