#pragma once

#include "Object.h"

#include <btBulletDynamicsCommon.h>





class PhysicalObject
{
public:

	struct Properties
	{
		btScalar m_mass;
	};


	PhysicalObject(Object* parent, const Properties& properties);
	virtual ~PhysicalObject();

	btRigidBody* getBody();

	void act();

protected:

	Object* parent;


	btCollisionShape* m_shape;
	btRigidBody* m_body;

	btTransform* m_transform;
};




class PhysicalObjectSphere :
	public PhysicalObject
{
public:
	PhysicalObjectSphere(Object* parent, const Properties& properties);
	virtual ~PhysicalObjectSphere();

};

class PhysicalObjectPrism :
	public PhysicalObject
{
public:
	PhysicalObjectPrism(Object* parent, const Properties& properties);
	virtual ~PhysicalObjectPrism();
};

