#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "window_gl.h"
#include <iostream>

#include <cmath>

#define PI 3.14159265359f

class Camera
{
public:
	Camera(int& width, int& height, bool* input, float zoom = 50, glm::vec3 focus = glm::vec3(0, 0, 0), glm::vec3 direction = glm::vec3(0, 0, 1));
	
	glm::f32* getProjection();
	glm::mat4& getView();
	glm::vec3& getFocus();

	
	void rotateCamera(float x, float y);


	void adjust(GLFWwindow* window);
	void refresh();


	float zoom_;

private:
	void moveCamera();

private:
	glm::vec3 focus_;
	glm::vec3 direction_;
	glm::vec3 up_;

	glm::f32* projectionPtr_;

	glm::mat4 projection_;
	glm::mat4 view_;

	float angleH_;
	float angleV_;

	bool* input_;

	int& width_;
	int& height_;

	float speed = 0.01;
};

