#pragma once

#include "Object.h"

#include <btBulletDynamicsCommon.h>


class PhysicalObject
{
public:
	PhysicalObject(Object* parent);
	~PhysicalObject();

	btRigidBody* getBody();

	virtual void act();

protected:

	Object* parent;


	btCollisionShape* shape;
	btRigidBody* body;
};




class PhysicalObjectSphere :
	public PhysicalObject
{
public:
	PhysicalObjectSphere(Object* parent);
	~PhysicalObjectSphere();

	virtual void act();

private:

};

class PhysicalObjectPrism :
	public PhysicalObject
{
public:
	PhysicalObjectPrism(Object* parent);
	~PhysicalObjectPrism();

	virtual void act();

private:

};

