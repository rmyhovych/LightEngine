#pragma once

#include <btBulletDynamicsCommon.h>

#include "PhysicalObject.h"

class PhysicalWorld
{
public:
	PhysicalWorld(const btVector3& gravity = btVector3(0, -10, 0));
	~PhysicalWorld();

	void linkSphere(Object* object, const PhysicalObject::Properties& properties);
	void linkPrism(Object* object, const PhysicalObject::Properties& properties);


	void step(double fps);

private:

	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;

	btDiscreteDynamicsWorld* dynamicsWorld;

	std::vector<PhysicalObject*> objects;
};

