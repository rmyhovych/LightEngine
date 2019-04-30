#pragma once
#include "ObjectManagerAbs.h"



class PhantomManagerV :
	public ObjectManagerAbs
{
public:
	PhantomManagerV(const std::string& vertexPath);
	virtual ~PhantomManagerV();

	virtual void render(ObjectUniforms& uniforms);


	GraphicalObject* createObject(
		const glm::vec3& position = glm::vec3(0),
		const glm::vec3& orientation = glm::vec3(0),
		const glm::vec3& scale = glm::vec3(1),
		const glm::vec3& color = glm::vec3(1));
};

