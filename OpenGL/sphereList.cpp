#include "sphereList.h"



SphereList::SphereList(const char* vertexPath, const char* fragmentPath, Camera& camera, std::vector<Light>& lights) :
	ObjectList(vertexPath, fragmentPath, camera, lights)
{
	std::ifstream bufferData("data/sphereBuffer", std::ios::binary);
	std::ifstream elementData("data/sphereElements", std::ios::binary);

	int bCount;
	bufferData.read((char*)&bCount, sizeof(bCount));

	int eCount;
	elementData.read((char*)&eCount, sizeof(eCount));


	float* buffer = new float[bCount];
	for (int i = 0; i < bCount; i++)
	{
		bufferData.read((char*)&(buffer[i]), sizeof(float));
	}
	bufferData.close();

	GLuint* elements = new GLuint[eCount];
	for (int i = 0; i < eCount; i++)
	{
		elementData.read((char*)&(elements[i]), sizeof(GLuint));
	}
	elementData.close();


	shader_.addBufferObject(buffer, bCount, 3);
	shader_.addElementObject(elements, eCount);

	delete[] buffer;
	delete[] elements;

	shader_.addLayout(0, 3, 0);
	shader_.addLayout(1, 3, 0);
}

void SphereList::addSphere(glm::vec3 position, float radius, glm::vec3 color)
{
	Object sphere = Object(position, glm::vec3(radius), color);

	sphere.linkColor("uColor", shader_.ID);
	sphere.linkModel("uModel", shader_.ID);
	sphere.linkRotation("uRotation", shader_.ID);

	objects_.push_back(sphere);
}
