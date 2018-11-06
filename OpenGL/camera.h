#pragma once

#include "base.h"

class Camera
{
public:
	Camera(bool* input, glm::vec3 position = glm::vec3(0, 0, 1), glm::vec3 focus = glm::vec3(0, 0, 0), float zoom = 1);

	float* passAngles();

	void move();

private:
	glm::vec3 position_;
	glm::vec3 focus_;
	glm::vec3 up_;

	float zoom_;

	glm::mat4 view_;

	float* angles_;

	bool* input_;
};

