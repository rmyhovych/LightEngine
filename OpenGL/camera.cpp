#include "camera.h"

Camera::Camera(bool* input, glm::vec3 position, glm::vec3 focus, float zoom) :
	input_(input),
	position_(position),
	focus_(focus),
	zoom_(zoom),
	up_(glm::vec3(0, 1, 0))
{
	view_ = glm::lookAt(zoom * position_, focus_, up_);
}

void Camera::rotateCamera(float x, float y)
{
	angleH_ += x;
	angleV_ += y;

	if (angleH_ < 0)
	{
		angleH_ += 2 * PI;
	}
	else if (angleH_ > 2 * PI)
	{
		angleH_ -= 2 * PI;
	}

	if (angleV_ > PI)
	{
		angleV_ = PI;
	}
	else if (angleV_ < 0)
	{
		angleV_ = 0;
	}
}


void Camera::move()
{
	
}
