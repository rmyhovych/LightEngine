#include "object.h"



Object::Object(glm::vec3& position, glm::vec3& scale, glm::vec3& color) :
	position_(position),
	scale_(scale),
	color_(color),

	rotation_(glm::mat3(1)),
	model_(glm::mat4(1)),

	modified_(0xff)
{
}

void Object::update()
{
	if (modified_ & 0b1 == 0b1)
	{

	}
}

