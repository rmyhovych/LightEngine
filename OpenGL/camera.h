#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

#include <cmath>

#define PI 3.14159265359f

class Camera
{
public:
	Camera(double* time, int width, int height, bool* input, 
		float zoom = 50, glm::vec3 focus = glm::vec3(0, 0, 0), glm::vec3 direction = glm::vec3(0, 0, 1));
	
	glm::f32* getProjection();
	glm::mat4& getView();
	glm::vec3& getFocus();
	glm::vec3& getPosition();

	
	void rotateCamera(float x, float y);


	void update();


	float zoom;

	glm::vec3 focus;

private:
	void moveCamera();

private:
	double* time;

	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 up;

	glm::f32* projectionPtr;

	glm::mat4 projection;
	glm::mat4 view;

	float angleH;
	float angleV;

	const float fov;

	bool* input;

	int width;
	int height;


	float speeds[3];

	const float acceleration;
	const float friction;
};

