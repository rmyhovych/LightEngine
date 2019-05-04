#include "DirLight.h"
#include <cmath>



DirLight::DirLight(float angleH, float angleV, const glm::vec3& focus, float shadowSize) :
	m_angleH(angleH),
	m_angleV(angleV),

	m_focus(focus),
	m_shadowSize(shadowSize)
{
	m_projection = glm::ortho(-shadowSize, shadowSize, -shadowSize, shadowSize, 0.0f, 2 * shadowSize);


	update();
}


glm::mat4& DirLight::getLightSpace()
{
	return m_lightSpace;
}

glm::vec3& DirLight::getDirection()
{
	return m_direction;
}


void DirLight::rotate(float deltaH, float deltaV)
{
	m_angleH += deltaH;
	m_angleV += deltaV;

	update();
}


void DirLight::setFocus(glm::vec3& focus)
{
	m_focus = focus;

	update();
}


void DirLight::update()
{
	m_direction.x = (float)(std::sin(m_angleH) * std::sin(m_angleV));
	m_direction.z = (float)(std::cos(m_angleH) * std::sin(m_angleV));
	m_direction.y = (float)(std::cos(m_angleV));

	glm::vec3 position = m_focus - (m_direction * m_shadowSize);

	glm::mat4 view = glm::lookAt(position, m_focus, glm::vec3(0, 1, 0));

	m_lightSpace = m_projection * view;
}

