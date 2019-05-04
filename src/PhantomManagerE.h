#pragma once

#include "ObjectManagerAbs.h"

class PhantomManagerE : 
	public ObjectManagerAbs
{
public:
	PhantomManagerE(const std::string& vertexPath, const std::string& elementPath);
	virtual ~PhantomManagerE();

	virtual void render(ObjectUniforms& uniforms);
	virtual void renderDepth(GLint modelIndex) ;


	GraphicalObject* createObject(
		const glm::vec3& position = glm::vec3(0),
		const glm::vec3& orientation = glm::vec3(0),
		const glm::vec3& scale = glm::vec3(1),
		const glm::vec3& color = glm::vec3(1));

};

