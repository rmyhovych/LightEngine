#include "Camera.h"

static const float fovy = PI / 3;

Camera::Camera(int width, int height, float zoom, float angleH, float angleV, const glm::vec3& focus) :
	zoom(zoom),

	focus(focus),
	up(glm::vec3(0, 1, 0)),

	angleH(angleH),
	angleV(angleV)
{
	projection = glm::perspective(fovy, ((float)width / (float)height), 0.1f, 500.0f);
	update();
}


void Camera::resize(int width, int height)
{
	projection = glm::perspective(fovy, ((float)width / (float)height), 0.1f, 500.0f);
	update();
}

glm::mat4& Camera::getPV()
{
	return pv;
}

void Camera::rotate(float x, float y)
{
	angleH -= x;
	angleV += y;

	if (angleH < 0)
	{
		angleH += 2 * PI;
	}
	else if (angleH > 2 * PI)
	{
		angleH -= 2 * PI;
	}

	if (angleV > PI - 0.01)
	{
		angleV = PI - 0.01;
	}
	else if (angleV < 0.01)
	{
		angleV = 0.01;
	}

	update();
}

void Camera::move(float x, float y, float z)
{
	focus += glm::vec3(x, y, z);

	update();
}

void Camera::setFocus(const glm::vec3& f)
{
	focus = f;
	update();
}


void Camera::update()
{
	direction.x = sin(angleH) * sin(angleV);
	direction.z = cos(angleH) * sin(angleV);
	direction.y = cos(angleV);

	position = focus - zoom * direction;


	view = glm::lookAt(position, focus, up);
	pv = projection * view;
}

