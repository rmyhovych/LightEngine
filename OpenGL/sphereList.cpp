#include "sphereList.h"



SphereList::SphereList(const char* vertexPath, const char* fragmentPath, Camera& camera, std::vector<Light>& lights) :
	shader_(Shader(vertexPath, fragmentPath)),
	camera_(camera),
	lights_(lights)
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
}

void SphereList::init()
{
	viewPtr_ = glGetUniformLocation(shader_.ID, "uView");
	projectionPtr_ = glGetUniformLocation(shader_.ID, "uProjection");
	sizePtr_ = glGetUniformLocation(shader_.ID, "uSize");

	LightPtr ptr;

	for (int i = 0; i < lights_.size(); i++)
	{
		ptr.color_ = glGetUniformLocation(shader_.ID, ("uLights[" + std::to_string(i) + "].color").c_str());
		ptr.pos_ = glGetUniformLocation(shader_.ID, ("uLights[" + std::to_string(i) + "].pos").c_str());
		ptr.intensity_ = glGetUniformLocation(shader_.ID, ("uLights[" + std::to_string(i) + "].intensity").c_str());

		lightsPtr_.push_back(ptr);
	}

	viewPosPtr_ = glGetUniformLocation(shader_.ID, "uProjection");
}

void SphereList::addSphere(glm::vec3 position, float radius, glm::vec3 color)
{
	Object sphere = Object(position, glm::vec3(radius), color);

	sphere.linkColor("uColor", shader_.ID);
	sphere.linkModel("uModel", shader_.ID);
	sphere.linkRotation("uRotation", shader_.ID);

	spheres_.push_back(sphere);
}

Object& SphereList::operator[](int index)
{
	return spheres_[index];
}

void SphereList::draw()
{
	shader_.use();

	if (lights_.size() != lightsPtr_.size())
	{
		LightPtr ptr;

		for (int i = lightsPtr_.size(); i < lights_.size(); i++)
		{
			ptr.color_ = glGetUniformLocation(shader_.ID, ("uLights[" + std::to_string(i) + "].color").c_str());
			ptr.pos_ = glGetUniformLocation(shader_.ID, ("uLights[" + std::to_string(i) + "].pos").c_str());
			ptr.intensity_ = glGetUniformLocation(shader_.ID, ("uLights[" + std::to_string(i) + "].intensity").c_str());

			lightsPtr_.push_back(ptr);
		}
	}

	for (int i = 0; i < lights_.size(); i++)
	{
		glUniform3f(lightsPtr_[i].color_, lights_[i].color.x, lights_[i].color.y, lights_[i].color.z);
		glUniform3f(lightsPtr_[i].pos_, lights_[i].pos.x, lights_[i].pos.y, lights_[i].pos.z);
		glUniform1f(lightsPtr_[i].intensity_, lights_[i].intensity);
	}

	glUniformMatrix4fv(viewPtr_, 1, GL_FALSE, glm::value_ptr(camera_.getView()));
	glUniformMatrix4fv(projectionPtr_, 1, GL_FALSE, camera_.getProjection());
	glUniform1i(sizePtr_, lights_.size());

	glm::vec3 cameraPos = camera_.getPosition();
	glUniform3f(viewPosPtr_, cameraPos.x, cameraPos.y, cameraPos.z);

	for (int i = 0; i < spheres_.size(); i++)
	{
		spheres_[i].use();
		shader_.draw();
	}

}

