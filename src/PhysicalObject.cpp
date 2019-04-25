#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(Object* parent, const Properties& properties) :
	parent(parent)
{
}

PhysicalObject::~PhysicalObject()
{
	delete m_shape;
	m_shape = nullptr;
}

btRigidBody* PhysicalObject::getBody()
{
	return m_body;
}



void PhysicalObject::act()
{
	btVector3& pos = m_transform->getOrigin();

	parent->setPosition(glm::vec3(pos.getX(), pos.getY(), pos.getZ()));
}






PhysicalObjectSphere::PhysicalObjectSphere(Object* parent, const Properties& properties) :
	PhysicalObject(parent, properties)
{
	glm::vec3 scale = parent->getScale();
	glm::vec3 position = parent->getPosition();

	btScalar radius = scale.x;
	btVector3 btPosition(position.x, position.y, position.z);


	m_shape = new btSphereShape(radius);

	btTransform startTransform;
	startTransform.setIdentity();

	btVector3 localInertia(0, 0, 0);

	m_shape->calculateLocalInertia(properties.m_mass, localInertia);

	startTransform.setOrigin(btPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(properties.m_mass, myMotionState, m_shape, localInertia);

	m_body = new btRigidBody(rbInfo);
	m_body->setRestitution(0.7);

	m_transform = &m_body->getWorldTransform();
}




PhysicalObjectSphere::~PhysicalObjectSphere()
{
}




void PhysicalObjectSphere::act()
{
	PhysicalObject::act();
}






PhysicalObjectPrism::PhysicalObjectPrism(Object* parent, const Properties& properties) :
	PhysicalObject(parent, properties)
{
	glm::vec3 scale = parent->getScale();
	glm::vec3 position = parent->getPosition();
	glm::quat orientation = parent->getOrientation();
	
	btVector3 btScale(scale.x, scale.y, scale.z);
	btVector3 btPosition(position.x, position.y, position.z);
	btQuaternion btOrientation(orientation.w, orientation.x, orientation.y, orientation.z);

	m_shape = new btBoxShape(btScale);

	btTransform startTransform;
	startTransform.setIdentity();

	btVector3 localInertia(0, 0, 0);

	m_shape->calculateLocalInertia(properties.m_mass, localInertia);

	startTransform.setOrigin(btPosition);
	startTransform.setRotation(btOrientation);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(properties.m_mass, myMotionState, m_shape, localInertia);

	m_body = new btRigidBody(rbInfo);
	m_body->setRestitution(0.5);

	m_transform = &m_body->getWorldTransform();
}

PhysicalObjectPrism::~PhysicalObjectPrism()
{
}

void PhysicalObjectPrism::act()
{
	PhysicalObject::act();

	btQuaternion orientation = m_transform->getRotation();

	parent->setOrientation(glm::mat4_cast(glm::quat(orientation.getW(), orientation.getX(),
		orientation.getY(), orientation.getZ())));
}
