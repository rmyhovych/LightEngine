#include "Object.h"
#include "PhysicalWorld.h"



Object::Object(GraphicalObject* parent, const Properties& properties) :
	parent(parent)
{
	btTransform transform;
	transform.setIdentity();

	btVector3 localInertia(0, 0, 0);


	properties.m_shape->calculateLocalInertia(properties.m_mass, localInertia);


	btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(properties.m_mass, myMotionState, properties.m_shape, localInertia);

	m_body = new btRigidBody(rbInfo);
	m_body->setRestitution(properties.m_restitution);
	m_body->setFriction(properties.m_friction);

	m_transform = &m_body->getWorldTransform();
}

Object::Object(GraphicalObject* parent, btEmptyShape* shape) :
	parent(parent)
{
	btTransform transform;
	transform.setIdentity();

	btVector3 localInertia(0, 0, 0);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, shape, localInertia);

	m_body = new btRigidBody(rbInfo);

	m_transform = &m_body->getWorldTransform();
}



Object::~Object()
{
}

btRigidBody* Object::getBody()
{
	return m_body;
}



void Object::impulse(const btVector3& force)
{
	m_body->applyCentralImpulse(force);
}

void Object::push(const btVector3& force)
{
	m_body->applyCentralForce(force);
}



void Object::setPosition(const btVector3& position)
{
	m_transform->setOrigin(position);

	act();
}

void Object::setRotation(const btVector3& rotation)
{
	btQuaternion rotQ;

	rotQ.setEuler(rotation.getY(), rotation.getX(), rotation.getZ());
	m_transform->setRotation(rotQ);

	act();
}



btVector3& Object::getPosition()
{
	return m_transform->getOrigin();
}



void Object::act()
{
	m_transform->getOpenGLMatrix(parent->getMovementPtr());

	parent->model();
}