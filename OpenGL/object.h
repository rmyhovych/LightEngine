#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Object
{
public:
	Object();
	~Object();

protected:
	glm::vec3 position_;
	glm::vec3 scale_;
	
	glm::mat4 rotation_;
	glm::mat4 model_;

	glm::vec3 color_;

};

