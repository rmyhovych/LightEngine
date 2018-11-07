#include "camera.h"

Camera::Camera(bool* input, float zoom, glm::vec3 focus, glm::vec3 direction) :
	input_(input),
	zoom_(zoom),
	focus_(focus),
	direction_(direction),
	up_(glm::vec3(0, 1, 0)),

	angleH_(0),
	angleV_(PI/2)
{

	view_ = glm::lookAt(focus_ - zoom * direction_, focus_, up_);
}

glm::mat4& Camera::getView()
{
	return view_;
}

void Camera::rotateCamera(float x, float y)
{
	angleH_ -= x;
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
		focus_ += speed * forward;
	}
	if (input_[1])
	{
		focus_ -= speed * forward;
	}
	if (input_[2])
	{
		focus_ += speed * right;
	}
	if (input_[3])
	{
		focus_ -= speed * right;
	}
	if (input_[4])
	{
		focus_ += speed * up_;
	}
	if (input_[5])
	{
		focus_ -= speed * up_;
	}
}


void Camera::refresh()
{
	moveCamera();

	direction_.x = sin(angleH_) * sin(angleV_);
	direction_.z = cos(angleH_) * sin(angleV_);
	direction_.y = cos(angleV_);

	view_ = glm::lookAt(focus_ - zoom_ * direction_, focus_, up_);
}
