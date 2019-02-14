#include "camera.h"

Camera::Camera(double* time, int width, int height, bool* input, float zoom, glm::vec3 focus, glm::vec3 direction) :
	time(time),


	input(input),
	zoom(zoom),
	focus(focus),
	direction(direction),
	up(glm::vec3(0, 1, 0)),

	angleH(0),
	angleV(PI/2),

	fov(PI/3),

	width(width),
	height(height),

	acceleration(0.3),
	friction(0.96)
{
	projection = glm::perspective(fov, ((float)width / (float)height), 0.1f, 1000.0f);
	projectionPtr = glm::value_ptr(projection);

	view = glm::lookAt(focus - zoom * direction, focus, up);
}



glm::mat4& Camera::getView()
{
	return view;
}

glm::vec3& Camera::getFocus()
{
	return focus;
}

glm::vec3& Camera::getPosition()
{
	return position;
}

glm::f32* Camera::getProjection()
{
	return projectionPtr;
}

void Camera::rotateCamera(float x, float y)
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
}

void Camera::moveCamera()
{
	glm::vec3 right = glm::normalize(glm::cross(direction, up));
	glm::vec3 forward = direction;

	if (input[0])
	{
		speeds[0] += acceleration;
	}
	if (input[1])
	{
		speeds[0] -= acceleration;
	}
	if (input[2])
	{
		speeds[1] += acceleration;
	}
	if (input[3])
	{
		speeds[1] -= acceleration;
	}
	if (input[4])
	{
		speeds[2] += acceleration;
	}
	if (input[5])
	{
		speeds[2] -= acceleration;
	}

	focus += (float)(*time) * (speeds[0] * forward + speeds[1] * right + speeds[2] * up);

	for (int i = 0; i < 3; i++)
	{
		speeds[i] *= friction;
	}
}


void Camera::update()
{
	moveCamera();

	direction.x = sin(angleH) * sin(angleV);
	direction.z = cos(angleH) * sin(angleV);
	direction.y = cos(angleV);

	position = focus - zoom * direction;


	view = glm::lookAt(position, focus, up);
}

