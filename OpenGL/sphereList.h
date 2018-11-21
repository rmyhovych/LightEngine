#pragma once

#include <vector>
#include <cmath>

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

struct Parameters
{
	float radius;
	glm::vec3 position;
	glm::vec3 color;
	glm::mat4 model;
};

class SphereList
{
public:
	SphereList(const char* vertexPath, const char* fragmentPath);
	void addSphere();

	void draw(std::vector<Light>& lights, Camera& camera);
private:
	std::vector<Parameters> params_;

	Shader shader_;
};

