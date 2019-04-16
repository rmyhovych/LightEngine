#include "camera.h"

Camera::Camera(int width, int height, float zoom, const glm::vec3& focus, const glm::vec3& direction) :
	
	focus(focus),
	direction(direction),
	up(glm::vec3(0, 1, 0)),

	angleH(0),
	angleV(PI/2)
{
	projection = glm::perspective(PI / 3, ((float)width / (float)height), 0.1f, 1000.0f);
	view = glm::lookAt(focus - zoom * direction, focus, up);
}


glm::mat4& Camera::getVP()
{
	return vp;
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


void Camera::update()
{
	direction.x = sin(angleH) * sin(angleV);
	direction.z = cos(angleH) * sin(angleV);
	direction.y = cos(angleV);

	position = focus - zoom * direction;


	view = glm::lookAt(position, focus, up);
	vp = view * projection;
}

