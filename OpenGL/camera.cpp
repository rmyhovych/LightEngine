#include "camera.h"

Camera::Camera(bool* input, glm::vec3 position, glm::vec3 focus, float zoom) :
	input_(input),
	position_(position),
	focus_(focus),
	zoom_(zoom),
	up_(glm::vec3(0, 1, 0))
{
	view_ = glm::lookAt(zoom * position_, focus_, up_);
	float* angles_ = new float[2]{0, 0};
}

float* Camera::passAngles()
{
	return nullptr;
}

void Camera::move()
{
	
}
