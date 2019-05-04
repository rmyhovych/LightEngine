#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#define PI 3.14159265359f

class DirLight
{
public:

	DirLight(
		float angleH = PI / 3,
		float angleV = 2 * PI / 3,
		const glm::vec3& focus = { 0, 0, 0 },
		float shadowSize = 10);


	glm::mat4& getLightSpace();

	glm::vec3& getDirection();


	void rotate(float deltaH, float deltaV);

	void setFocus(glm::vec3& focus);

private:

	void update();


	glm::vec3 m_focus;
	glm::mat4 m_projection;

	glm::mat4 m_lightSpace;

	glm::vec3 m_direction;


	float m_angleH;
	float m_angleV;

	float m_shadowSize;
};

