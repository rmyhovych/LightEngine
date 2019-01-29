#include "sphereList.h"



SphereList::SphereList(const char* vertexPath, const char* fragmentPath, Camera& camera, std::vector<Light>& lights) :
	ObjectList(vertexPath, fragmentPath, camera, lights)
{
	//createSphere(100, 100);

	std::ifstream bufferData("data/sphereBuffer", std::ios::binary);
	std::ifstream elementData("data/sphereElements", std::ios::binary);

	int bCount;
	bufferData.read((char*)&bCount, sizeof(bCount));

	int eCount;
	elementData.read((char*)&eCount, sizeof(eCount));


	float* buffer = new float[bCount];
	for (int i = 0; i < bCount + 1; i++)
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


	shader_.addBufferObject(buffer, bCount / 3, 3);
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





void createSphere(int meridianSize, int parallelSize)
{
	float* buffer = new float[((parallelSize * meridianSize) + 2) * 3];


	float* meridians = new float[meridianSize];
	float* parallels = new float[parallelSize];

	for (int i = 0; i < meridianSize; i++)
	{
		meridians[i] = i * (2 * PI / meridianSize);
	}

	for (int i = 0; i < parallelSize; i++)
	{
		parallels[i] = (i + 1) * (PI / (parallelSize + 1));
	}


	int bCount = 0;
	float* top = new float[3]{ 0, 1, 0 };
	for (int i = 0; i < 3; i++)
	{
		buffer[bCount++] = top[i];
	}
	delete[] top;

	for (int y = 0; y < parallelSize; y++)
	{
		for (int x = 0; x < meridianSize; x++)
		{
			buffer[bCount++] = sin(parallels[y]) * cos(meridians[x]);
			buffer[bCount++] = cos(parallels[y]);
			buffer[bCount++] = sin(parallels[y]) * sin(meridians[x]);
		}
	}

	float* bot = new float[3]{ 0, -1, 0 };
	for (int i = 0; i < 3; i++)
	{
		buffer[bCount++] = bot[i];
	}

	delete[] bot;
	delete[] meridians;
	delete[] parallels;


	GLuint* elements = new GLuint[3 * 2 * (meridianSize) * (parallelSize)];


	int eCount = 0;
	for (int i = 0; i < meridianSize; i++)
	{
		elements[eCount++] = 0;
		elements[eCount++] = (i + 1);
		elements[eCount++] = ((i + 1) % meridianSize) + 1;
	}


	for (int i = 0; i < parallelSize - 1; i++)
	{
		for (int j = 0; j < meridianSize; j++)
		{
			elements[eCount++] = (i * meridianSize + j + 1);
			elements[eCount++] = ((i + 1) * meridianSize + j + 1);
			elements[eCount++] = (((i + 1) * meridianSize) + ((1 + j) % meridianSize) + 1);

			elements[eCount++] = (i * meridianSize + j + 1);
			elements[eCount++] = (((i + 1) * meridianSize) + ((1 + j) % meridianSize) + 1);
			elements[eCount++] = (i * meridianSize + ((j + 1) % meridianSize) + 1);
		}
	}


	int bufferSize = bCount / 3;
	for (int i = bufferSize - meridianSize; i < bufferSize; i++)
	{
		elements[eCount++] = bufferSize - 1;
		elements[eCount++] = (((i - (bufferSize - meridianSize) + 1) % meridianSize) + (bufferSize - meridianSize)) - 1;
		elements[eCount++] = i - 1;
	}


	std::ofstream sphereBuffer("data/sphereBuffer", std::ios::binary);
	sphereBuffer.write((char*)&bCount, sizeof(bCount));
	for (int i = 0; i < bCount; i++)
	{
		sphereBuffer.write((char*)&(buffer[i]), sizeof(float));
	}
	sphereBuffer.close();

	std::ofstream sphereElements("data/sphereElements", std::ios::binary);
	sphereElements.write((char*)&eCount, sizeof(eCount));
	for (int i = 0; i < eCount; i++)
	{
		sphereElements.write((char*)&(elements[i]), sizeof(GLuint));
	}
	sphereElements.close();
}