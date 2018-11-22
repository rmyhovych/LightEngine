#include "prismList.h"



PrismList::PrismList(const char* vertexPath, const char* fragmentPath, Camera& camera, std::vector<Light>& lights) :
	ObjectList(vertexPath, fragmentPath, camera, lights)
{
	float vertices[] = {
		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		// Left face
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		// Right face
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 // Bottom face          
		 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 // Top face
		 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	};


	shader_.addBufferObject(vertices, 36, 6);

	shader_.addLayout(0, 3, 0);
	shader_.addLayout(1, 3, 3);
}

void PrismList::addPrism(glm::vec3 position, glm::vec3 scale, glm::vec3 color)
{
	Object prism = Object(position, scale, color);

	prism.linkColor("uColor", shader_.ID);
	prism.linkModel("uModel", shader_.ID);
	prism.linkRotation("uRotation", shader_.ID);

	objects_.push_back(prism);

}

