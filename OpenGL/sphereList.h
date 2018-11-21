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

class SphereList
{
public:
	SphereList(const char* vertexPath, const char* fragmentPath);
	~SphereList();

	void init(std::vector<Light>& lights);

	void addSphere(glm::vec3& position, float radius, glm::vec3& color);

	void draw(std::vector<Light>& lights, Camera& camera);
private:
	std::vector<Object> spheres_;

	Shader shader_;

	GLuint viewPtr_;
	GLuint projectionPtr_;
	GLuint sizePtr_;
	GLuint* lightsPtr_;
	GLuint viewPosPtr_;
};

