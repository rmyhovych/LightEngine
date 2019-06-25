#pragma once

#include "ObjectManager.h"


class SphereManager :
	public ObjectManager
{
public:
	SphereManager();
	virtual ~SphereManager();

	virtual void render(ObjectUniforms& uniforms);

	virtual void renderDepth(GLint modelIndex);

	virtual Object* createObject(
		btScalar mass = 1.0,
		btScalar restitution = 0.5,
		btScalar friction = 0.5,
		const glm::vec3& position = glm::vec3(0),
		const glm::vec3& color = glm::vec3(1),
		const glm::vec3& scale = glm::vec3(1));
};

