#include "dirLight.h"
#include <cmath>



DirLight::DirLight()
{
}


void DirLight::init(float angleH, float angleV)
{
	this->angleH = angleH;
	this->angleV = angleV;

	shadowLimit = Engine::camera->zoom;

	projection = glm::ortho(-shadowLimit, shadowLimit, -shadowLimit, shadowLimit, 0.0f, 2 * shadowLimit);


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
	glm::vec3& focus = Engine::camera->focus;

	glm::vec3 position = focus - (direction * shadowLimit);

	glm::mat4 view = glm::lookAt(position, focus, glm::vec3(0, 1, 0));

	lightSpace = projection * view;
}

void DirLight::setDirection()
{
	direction.x = (float)(std::sin(angleH) * std::sin(angleV));
	direction.z = (float)(std::cos(angleH) * std::sin(angleV));
	direction.y = (float)(std::cos(angleV));
}
