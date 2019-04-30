#pragma once

#include "Shader.h"
#include "UniformHandling.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


class GraphicalObject
{
public:

	GraphicalObject(
		const glm::vec3& color = glm::vec3(1), 
		const glm::vec3& scale = glm::vec3(1));


	float* getMovementPtr();

	void setMovement(const glm::vec3& position, const glm::vec3& rotation);


	glm::vec3 getScale();

	void setScale(const glm::vec3& v);



	void setColor(const glm::vec3& color);


	void useDepth();

	void use(ObjectUniforms& uniforms);


	void model();


private:

	glm::mat4 mScale;
	
	glm::mat4 mMovement;
	glm::mat4 mModel;


	glm::vec3 color;
};







