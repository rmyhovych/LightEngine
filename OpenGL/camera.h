#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

#include <cmath>

#define PI 3.14159265359f

class Camera
{
public:
	Camera(bool* input, glm::vec3 position = glm::vec3(0, 0, 1), glm::vec3 direction = glm::vec3(0, 0, 0));

	glm::mat4& getView();
	
	void rotateCamera(float x, float y);

	void refresh();

private:
	void moveCamera();

private:
	glm::vec3 position_;
	glm::vec3 direction_;
	glm::vec3 up_;

	glm::mat4 view_;

	float angleH_;
	float angleV_;

	bool* input_;

	float speed = 0.05;
};

