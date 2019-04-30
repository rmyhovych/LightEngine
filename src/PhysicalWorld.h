#pragma once

#include <btBulletDynamicsCommon.h>

#include "PhysicalObject.h"

class PhysicalWorld
{
public:
	
	static PhysicalWorld* getInstance();
	
	~PhysicalWorld();

	PhysicalObject* createObject(GraphicalObject* parent, const PhysicalObject::Properties& properties);


	void step(double fps);

private:

	PhysicalWorld(const btVector3& gravity = btVector3(0, -10, 0));
	PhysicalWorld(const PhysicalWorld const&) = delete;
	PhysicalWorld& operator=(const PhysicalWorld const&) = delete;

	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;

	btDiscreteDynamicsWorld* dynamicsWorld;

	std::vector<PhysicalObject*> sObjects;
	std::vector<PhysicalObject*> dObjects;
};

 