#include "camera.h"

Camera::Camera(double& time, int& width, int& height, bool* input, float zoom, glm::vec3 focus, glm::vec3 direction) :
	time_(time),
	input_(input),
	zoom_(zoom),
	focus_(focus),
	direction_(direction),
	up_(glm::vec3(0, 1, 0)),

	angleH_(0),
	angleV_(PI/2),

	fov_(PI/3),

	width_(width),
	height_(height),

	acceleration_(0.3),
	friction_(0.96)
{
	projection_ = glm::perspective(fov_, ((float)width_ / (float)height_), 0.1f, 1000.0f);
	projectionPtr_ = glm::value_ptr(projection_);

	view_ = glm::lookAt(focus_ - zoom * direction_, focus_, up_);
}

glm::mat4& Camera::getView()
{
	return view_;
}

glm::vec3& Camera::getFocus()
{
	return focus_;
}

glm::vec3& Camera::getPosition()
{
	return position_;
}

glm::f32* Camera::getProjection()
{
	return projectionPtr_;
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
	//glm::vec3 forward = glm::normalize(glm::cross(up_, right));
	glm::vec3 forward = direction_;

	if (input_[0])
	{
		speeds_[0] += acceleration_;
	}
	if (input_[1])
	{
		speeds_[0] -= acceleration_;
	}
	if (input_[2])
	{
		speeds_[1] += acceleration_;
	}
	if (input_[3])
	{
		speeds_[1] -= acceleration_;
	}
	if (input_[4])
	{
		speeds_[2] += acceleration_;
	}
	if (input_[5])
	{
		speeds_[2] -= acceleration_;
	}

	focus_ += (float)time_ * (speeds_[0] * forward + speeds_[1] * right + speeds_[2] * up_);

	for (int i = 0; i < 3; i++)
	{
		speeds_[i] *= friction_;
	}
}


void Camera::adjust(GLFWwindow* window)
{
	int newW, newH;

	glfwGetWindowSize(window, &newW, &newH);

	if (newW != width_ || newH != height_)
	{
		width_ = newW;
		height_ = newH;

		projection_ = glm::perspective(fov_, ((float)width_ / (float)height_), 0.1f, 1000.0f);
		projectionPtr_ = glm::value_ptr(projection_);
	}
}

void Camera::refresh()
{
	moveCamera();

	direction_.x = sin(angleH_) * sin(angleV_);
	direction_.z = cos(angleH_) * sin(angleV_);
	direction_.y = cos(angleV_);

	position_ = focus_ - zoom_ * direction_;

	view_ = glm::lookAt(position_, focus_, up_);
}
