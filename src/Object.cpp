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


	PhysicalWorld* pw = PhysicalWorld::getInstance();

	properties.m_mass == 0 ? pw->addObjectStatic(this) : pw->addObjectDynamic(this);


	act();
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

	PhysicalWorld::getInstance()->addObjectStatic(this);


	act();
}

void Object::copyTransform(Object* secondObj)
{
	btScalar* matrix = new btScalar[16];
	
	secondObj->m_transform->getOpenGLMatrix(matrix);
	this->m_transform->setFromOpenGLMatrix(matrix);

	delete[] matrix;
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
	
	setRotation(rotQ);
}

void Object::setRotation(const btQuaternion& quaternion)
{
	m_transform->setRotation(quaternion);

	act();
}

void Object::setGravity(const btVector3& gravity)
{
	m_body->setGravity(gravity);
}

const btVector3& Object::getGravity()
{
	return m_body->getGravity();
}


void Object::translate(const btVector3& translation)
{
	m_body->translate(translation);
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