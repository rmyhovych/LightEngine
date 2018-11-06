#include "camera.h"

Camera::Camera(bool* input, glm::vec3 position, glm::vec3 direction) :
	input_(input),
	position_(position),
	direction_(direction),
	up_(glm::vec3(0, 1, 0))
{
	view_ = glm::lookAt(position_, direction_, up_);
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

	if (angleV_ > PI - 0.01)
	{
		angleV_ = PI - 0.01;
	}
	else if (angleV_ < 0.01)
	{
		angleV_ = 0.01;
	}
}

void Camera::moveCamera()
{
	glm::vec3 right = glm::normalize(glm::cross(direction_, up_));
	glm::vec3 forward = glm::normalize(glm::cross(up_, right));

	if (input_[0])
	{
		position_ += forward;
	}
	if (input_[1])
	{
		position_ -= forward;
	}
	if (input_[2])
	{
		position_ += right;
	}
	if (input_[3])
	{
		position_ -= right;
	}
	if (input_[4])
	{
		position_ += up_;
	}
	if (input_[5])
	{
		position_ -= up_;
	}
}


void Camera::refresh()
{
	direction_.x = sin(angleH_) * cos(angleV_);
	direction_.y = cos(angleH_) * cos(angleV_);
	direction_.z = sin(angleH_);

	view_ = glm::lookAt(position_, position_ + direction_, up_);
}
