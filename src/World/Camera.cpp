#include "Camera.h"

static const float fovy = PI / 3;

Camera::Camera(int width, int height, float zoom, float angleH, float angleV, const glm::vec3& focus) :
	m_zoom(zoom),

	m_focus(focus),
	m_up(glm::vec3(0, 1, 0)),

	m_angleH(angleH),
	m_angleV(angleV)
{
	resize(width, height);
}


void Camera::resize(int width, int height)
{
	m_projection = glm::perspective(fovy, ((float)width / (float)height), 0.1f, 5000.0f);
	update();
}

glm::mat4& Camera::getPV()
{
	return m_pv;
}

void Camera::rotate(float x, float y)
{
	m_angleH -= x;
	m_angleV += y;

	if (m_angleH < 0)
	{
		m_angleH += 2 * PI;
	}
	else if (m_angleH > 2 * PI)
	{
		m_angleH -= 2 * PI;
	}

	if (m_angleV > PI - 0.01)
	{
		m_angleV = PI - 0.01;
	}
	else if (m_angleV < 0.01)
	{
		m_angleV = 0.01;
	}

	update();
}

void Camera::move(float x, float y, float z)
{
	m_focus += glm::vec3(x, y, z);

	update();
}

void Camera::zoom(float delta)
{
	m_zoom += delta * m_zoom;
	update();
}

glm::vec3& Camera::getFocus()
{
	return m_focus;
}

void Camera::setFocus(const glm::vec3& focus, const glm::vec3& up)
{
	m_focus += 0.1f * (focus - m_focus);
	m_up += 0.1f * (up - m_up);

	update();
}


void Camera::update()
{
	m_position = m_focus - m_zoom * m_direction;

	m_view = glm::lookAt(m_position, m_focus, m_up);
	m_pv = m_projection * m_view;
}

void Camera::setZoom(float newZoom)
{
	m_zoom = newZoom;
	update();
}

void Camera::setDirection(const glm::vec3& direction)
{
	m_direction += 0.02f * (direction - m_direction);
}

