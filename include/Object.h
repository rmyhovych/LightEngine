#pragma once

#include "Shader.h"
#include "UniformHandling.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <btBulletCollisionCommon.h>


class Object
{
public:

	Object(
		const glm::vec3& position = glm::vec3(0), 
		const glm::vec3& orientation = glm::vec3(0),
		const glm::vec3& scale = glm::vec3(1),
		const glm::vec3& color = glm::vec3(1));




	void addPosition(const glm::vec3& position);

	void setPosition(const glm::vec3& position);



	void addOrientation(const glm::vec3& rotation);

	void setOrientation(const glm::vec3& rotation);




	void addScale(const glm::vec3& v);

	void setScale(const glm::vec3& v);

	void setScale(float v);



	void setColor(const glm::vec3& color);

	void setColor(float r, float g, float b);


	void useDepth();

	void use(ObjectUniforms& uniforms);

private:

	void model();


	static glm::vec3 right;
	static glm::vec3 top;
	static glm::vec3 back;


	glm::mat4 mScale;
	glm::mat4 mRotation;
	glm::mat4 mTranslation;

	glm::mat4 mModel;


	glm::vec3 color;


};







