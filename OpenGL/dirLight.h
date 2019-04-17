#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class DirLight
{
public:

	glm::mat4 lightSpace;

	glm::vec3 direction;


	DirLight(float angleH, float angleV, glm::vec3& focus, float shadowSize);


	void rotate(float deltaH, float deltaV);

	void update();

private:

	void setDirection();

	glm::vec3& focus;
	glm::mat4 projection;

	float angleH;
	float angleV;

	float shadowSize;
};

