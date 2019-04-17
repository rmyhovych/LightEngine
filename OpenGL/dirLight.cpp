#include "dirLight.h"
#include <cmath>



DirLight::DirLight(float angleH, float angleV, glm::vec3& focus, float shadowSize) :
	angleH(angleH),
	angleV(angleV),

	focus(focus),
	shadowSize(shadowSize)
{
	projection = glm::ortho(-shadowSize, shadowSize, -shadowSize, shadowSize, 0.0f, 2 * shadowSize);


	setDirection();
	update();
}


void DirLight::rotate(float deltaH, float deltaV)
{
	angleH += deltaH;
	angleV += deltaV;

	setDirection();
	update();
}

void DirLight::update()
{
	glm::vec3 position = focus - (direction * shadowSize);

	glm::mat4 view = glm::lookAt(position, focus, glm::vec3(0, 1, 0));

	lightSpace = projection * view;
}


void DirLight::setDirection()
{
	direction.x = (float)(std::sin(angleH) * std::sin(angleV));
	direction.z = (float)(std::cos(angleH) * std::sin(angleV));
	direction.y = (float)(std::cos(angleV));
}
