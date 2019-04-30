#include "PhysicalObject.h"
#include "PhysicalWorld.h"



PhysicalObject::PhysicalObject(GraphicalObject* parent, const Properties& properties) :
	parent(parent)
{
	btTransform startTransform;
	startTransform.setIdentity();

	btVector3 localInertia(0, 0, 0);

	properties.m_shape->calculateLocalInertia(properties.m_mass, localInertia);


	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(properties.m_mass, myMotionState, properties.m_shape, localInertia);

	m_body = new btRigidBody(rbInfo);
	m_body->setRestitution(properties.m_restitution);
	m_body->setFriction(properties.m_friction);

	m_transform = &m_body->getWorldTransform();
}



PhysicalObject::~PhysicalObject()
{
}

btRigidBody* PhysicalObject::getBody()
{
	return m_body;
}



void PhysicalObject::impulse(const btVector3& force)
{
	m_body->applyCentralImpulse(force);
}

void PhysicalObject::push(const btVector3& force)
{
	m_body->applyCentralForce(force);
}



void PhysicalObject::setPosition(const btVector3& position)
{
	m_transform->setOrigin(position);

	act();
}

void PhysicalObject::setRotation(const btVector3& rotation)
{
	btQuaternion rotQ;

	rotQ.setEuler(rotation.getY(), rotation.getX(), rotation.getZ());
	m_transform->setRotation(rotQ);

	act();
}



btVector3& PhysicalObject::getPosition()
{
	return m_transform->getOrigin();
}



void PhysicalObject::act()
{
	m_transform->getOpenGLMatrix(parent->getMovementPtr());

	parent->model();
}