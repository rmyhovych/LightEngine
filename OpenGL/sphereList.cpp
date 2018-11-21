#include "sphereList.h"



SphereList::SphereList(const char* vertexPath, const char* fragmentPath) :
	shader_(Shader(vertexPath, fragmentPath))
{
	const int meridianSize = 20;
	const int parallelSize = 20;
	float* buffer = new float[(parallelSize * meridianSize + 2) * 3];
	//float buffer[(parallelSize * meridianSize + 2) * 3];


	float* meridians = new float[meridianSize];
	float* parallels = new float[parallelSize];
	//float meridians[meridianSize];
	//float parallels[parallelSize];

	for (int i = 0; i < meridianSize; i++)
	{
		meridians[i] = i * (2 * PI / meridianSize);
	}

	for (int i = 0; i < parallelSize; i++)
	{
		parallels[i] = (i + 1) * (PI / (parallelSize + 1));
	}


	int bCount = 0;
	float* top = new float[3] {0, 1, 0};
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
	//GLuint elements[3 * 2 * (meridianSize) * (parallelSize)];


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

	shader_.addBufferObject(buffer, bCount, 3);
	shader_.addElementObject(elements, eCount);

	delete[] buffer;
	delete[] elements;

	shader_.addLayout(0, 3, 0);
	shader_.addLayout(1, 3, 0);

	viewPtr_ = glGetUniformLocation(shader_.ID, "uView");
	projectionPtr_ = glGetUniformLocation(shader_.ID, "uProjection");
	sizePtr_ = glGetUniformLocation(shader_.ID, "uSize");
	lightsPtr_ = glGetUniformLocation(shader_.ID, "uLights");
	viewPosPtr_ = glGetUniformLocation(shader_.ID, "uProjection");
}

void SphereList::addSphere(glm::vec3& position, float radius, glm::vec3& color)
{
	Object sphere = Object(position, glm::vec3(radius), color);

	sphere.linkColor("uColor", shader_.ID);
	sphere.linkModel("uModel", shader_.ID);
	sphere.linkRotation("uRotation", shader_.ID);

	spheres_.push_back(sphere);
}

void SphereList::draw(std::vector<Light>& lights, Camera& camera)
{
	Parameters param = { 1, glm::vec3(-1.5, -1.4, -6), glm::vec3(0.5, 0.7, 0.8) };
	param.model = glm::translate(glm::mat4(1.0f), param.position);
	param.model = glm::scale(param.model, param.radius * glm::vec3(1.0f));

	shader_.use();

	shader_.uniformInt("uSize", lights.size());
	for (int j = 0; j < lights.size(); j++)
	{
		shader_.uniformVec3(("uLights[" + std::to_string(j) + "].color").c_str(), lights[j].color);
		shader_.uniformVec3(("uLights[" + std::to_string(j) + "].pos").c_str(), lights[j].pos);
		shader_.uniformFloat(("uLights[" + std::to_string(j) + "].intensity").c_str(), lights[j].intensity);
	}

	//	Object
	shader_.uniformVec3("uColor", param.color);
	shader_.uniformVec3("uViewPos", camera.getPosition());


	//	- VERTEX -
	shader_.uniformMat4Ptr("uModel", glm::value_ptr(param.model));
	shader_.uniformMat4Ptr("uView", glm::value_ptr(camera.getView()));
	shader_.uniformMat4Ptr("uProjection", camera.getProjection());


	shader_.draw();
}

