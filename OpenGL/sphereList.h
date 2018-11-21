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

class SphereList
{
public:
	SphereList(const char* vertexPath, const char* fragmentPath);

	void init(Camera& camera, std::vector<Light>& lights);

	void addSphere(glm::vec3& position, float radius, glm::vec3& color);

	void draw();

private:
	std::vector<Object> spheres_;
	std::vector<Light>& lights_;
	std::vector<LightPtr> lightsPtr_;

	Shader shader_;
	Camera& camera_;

	GLuint viewPtr_;
	GLuint projectionPtr_;
	GLuint sizePtr_;

	GLuint viewPosPtr_;
};

