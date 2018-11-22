#include "objectList.h"
#include <fstream>


ObjectList::ObjectList(const char* vertexPath, const char* fragmentPath, Camera& camera, std::vector<Light>& lights) :
	shader_(Shader(vertexPath, fragmentPath)),
	camera_(camera),
	lights_(lights)
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

	viewPosPtr_ = glGetUniformLocation(shader_.ID, "uViewPos");
}

void ObjectList::addSphere(glm::vec3 position, float radius, glm::vec3 color)
{
}

void ObjectList::addPrism(glm::vec3 position, glm::vec3 scale, glm::vec3 color)
{
}

Object& ObjectList::operator[](int index)
{
	return objects_[index];
}

void ObjectList::draw()
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

	for (int i = 0; i < objects_.size(); i++)
	{
		objects_[i].use();
		shader_.draw();
	}

}

