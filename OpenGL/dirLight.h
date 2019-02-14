#pragma once

#include "engine.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class DirLight
{
public:

	glm::mat4 lightSpace;

	glm::vec3 direction;


	DirLight();

	void init(float angleH, float angleV);

	void rotate(float deltaH, float deltaV);

	void update();

private:

	void setDirection();


	glm::mat4 projection;

	float angleH;
	float angleV;

	float shadowLimit;
};

