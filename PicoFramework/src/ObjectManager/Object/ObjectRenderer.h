#pragma once

#include "Graphics/Shader.h"
#include "Graphics/UniformHandling.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class ObjectRenderer
{
public:

	ObjectRenderer(
		const glm::vec3& color = glm::vec3(1), 
		const glm::vec3& scale = glm::vec3(1));


	float* getMovementPtr();

	glm::vec3 getScale();

	void useDepth();

	void use(ObjectUniforms& uniforms);
	void useDepth(GLint modelIndex);


	void model();

private:

	glm::mat4 mScale;
	
	glm::mat4 mMovement;
	glm::mat4 mModel;


	glm::vec3 color;
};







