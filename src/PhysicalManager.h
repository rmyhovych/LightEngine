#pragma once

#include "ObjectManagerAbs.h"


class PhysicalManager :
	public ObjectManagerAbs
{
public:
	PhysicalManager();
	virtual ~PhysicalManager() = 0;

	virtual void render(ObjectUniforms& uniforms) = 0;

	virtual PhysicalObject* createObject(
		btScalar mass = 1.0,
		btScalar restitution = 0.5,
		btScalar friction = 0.5,
		const glm::vec3& position = glm::vec3(0),
		const glm::vec3& orientation = glm::vec3(0),
		const glm::vec3& scale = glm::vec3(1),
		const glm::vec3& color = glm::vec3(1)) = 0;
};

