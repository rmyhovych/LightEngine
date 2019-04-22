#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(Object* parent) :
	parent(parent)
{
}

PhysicalObject::~PhysicalObject()
{
	delete shape;
	shape = nullptr;
}

btRigidBody* PhysicalObject::getBody()
{
	return body;
}



void PhysicalObject::act()
{
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);

	btVector3 pos = transform.getOrigin();

	parent->setPosition(glm::vec3(pos.getX(), pos.getY(), pos.getZ()));
}






PhysicalObjectSphere::PhysicalObjectSphere(Object* parent) :
	PhysicalObject(parent)
{
	glm::vec3 scale = parent->getScale();
	glm::vec3 position = parent->getPosition();

	btScalar radius = scale.x;
	btVector3 btPosition(position.x, position.y, position.z);


	shape = new btSphereShape(radius);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(1.0f);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	btVector3 localInertia(0, 0, 0);

	if (mass != 0.0f)
		shape->calculateLocalInertia(mass, localInertia);

	startTransform.setOrigin(btPosition);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
	body = new btRigidBody(rbInfo);
}




PhysicalObjectSphere::~PhysicalObjectSphere()
{
}




void PhysicalObjectSphere::act()
{
	PhysicalObject::act();
}






PhysicalObjectPrism::PhysicalObjectPrism(Object* parent) :
	PhysicalObject(parent)
{
	glm::vec3 scale = parent->getScale();
	glm::vec3 position = parent->getPosition();

	
	btVector3 btScale(scale.x, scale.y, scale.z);
	btVector3 btPosition(position.x, position.y, position.z);


	shape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(0.0f);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	btVector3 localInertia(0, 0, 0);

	shape->calculateLocalInertia(mass, localInertia);

	startTransform.setOrigin(btPosition);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
	body = new btRigidBody(rbInfo);
}

PhysicalObjectPrism::~PhysicalObjectPrism()
{
}

void PhysicalObjectPrism::act()
{
	PhysicalObject::act();


}
