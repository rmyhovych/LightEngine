#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

#include <cmath>

#define PI 3.14159265359f

class Camera
{
public:
	Camera(int width, int height, float zoom = 20, 
		float angleH = 0, float angleV = PI / 2,
		const glm::vec3& focus = glm::vec3(0, 0, 0));
	
	
	glm::mat4& getPV();
	
	void rotate(float x, float y);
	void move(float x, float y, float z);


private:
	void update();

private:

	float zoom;

	glm::vec3 focus;
	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 up;

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 pv;


	float angleH;
	float angleV;
};
