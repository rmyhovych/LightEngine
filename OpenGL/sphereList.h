#pragma once
#include "objectList.h"

class SphereList :
	public ObjectList
{
public:
	SphereList(const char* vertexPath, const char* fragmentPath, Camera& camera, std::vector<Light>& lights);

	virtual void addSphere(glm::vec3 position, float radius, glm::vec3 color);
};

