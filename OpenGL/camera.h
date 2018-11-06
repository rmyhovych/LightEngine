#pragma once

#include "base.h"

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
};

