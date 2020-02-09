#pragma once

#include "ObjectRenderer.h"

#include <btBulletDynamicsCommon.h>


class Object
{
public:

	struct Properties
	{
		btCollisionShape* m_shape;
		btScalar m_mass = 1.0;
		btScalar m_restitution = 0.0;
		btScalar m_friction = 0.4;

		Properties(btCollisionShape* shape, btScalar mass, btScalar restitution, btScalar friction) :
			m_shape(shape),
			m_mass(mass),
			m_restitution(restitution),
			m_friction(friction)
		{
		}
	};


	Object(ObjectRenderer* parent, const Properties& properties);
	Object(ObjectRenderer* parent, btEmptyShape* shape);

	void copyTransform(Object* secondObj);

	~Object();

	btRigidBody* getBody();
	btTransform* getTransform();


	void impulse(const btVector3& force);
	void push(const btVector3& force);

	void setPosition(const btVector3& position);

	void setRotation(const btVector3& rotation);
	void setRotation(const btQuaternion& quaternion);

	void setGravity(const btVector3& gravity);
	const btVector3& getGravity();

	void translate(const btVector3& translation);
	void rotate(const btQuaternion& rotation);


	btVector3& getPosition();

	void act();

protected:

	ObjectRenderer* m_parent;

	btRigidBody* m_body;

	btTransform* m_transform;
};
