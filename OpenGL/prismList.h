#pragma once
#include "objectList.h"
class PrismList :
	public ObjectList
{
public:
	PrismList(const char* vertexPath, const char* fragmentPath, Camera& camera, std::vector<Light>& lights);

	virtual void addPrism(glm::vec3 position, glm::vec3 scale, glm::vec3 color);
};

