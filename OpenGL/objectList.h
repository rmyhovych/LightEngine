#pragma once

#include <vector>
#include <cmath>

#include "object.h"
#include "camera.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#ifndef PI
#define PI 3.14159265359f
#endif // !PI

struct Light
{
	glm::vec3 color;
	glm::vec3 pos;
	float intensity;
};

struct LightPtr
{
	GLuint color_;
	GLuint pos_;
	GLuint intensity_;
};

class ObjectList
{
public:
	ObjectList(const char* vertexPath, const char* fragmentPath, Camera& camera, std::vector<Light>& lights);

	virtual void addSphere(glm::vec3 position, float radius, glm::vec3 color);
	virtual void addPrism(glm::vec3 position, glm::vec3 scale, glm::vec3 color);

	Object& operator[](int index);

	void draw();

protected:
	std::vector<Object> objects_;
	std::vector<Light>& lights_;
	std::vector<LightPtr> lightsPtr_;

	Shader shader_;
	Camera& camera_;

	GLuint viewPtr_;
	GLuint projectionPtr_;
	GLuint sizePtr_;

	GLuint viewPosPtr_;
};

