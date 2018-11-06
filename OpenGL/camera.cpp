#include "camera.h"

Camera::Camera(bool* input, glm::vec3 position, glm::vec3 focus, float zoom) :
	input_(input),
	position_(position),
	focus_(focus),
	zoom_(zoom),
	up_(glm::vec3(0, 1, 0)),

	angleH_(0),
	angleV_(0)
{
	view_ = glm::lookAt(zoom * position_, focus_, up_);
}

float* Camera::passAngles()
{
	return nullptr;
}

void Camera::move()
{
	
}
