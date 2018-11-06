#pragma once
#include "base.h"

class Camera
{
public:
	Camera();

private:
	glm::vec3 position;
	glm::vec3 focus;
	float zoom;
};

