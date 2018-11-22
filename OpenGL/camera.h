#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "window.h"
#include <iostream>

#include <cmath>

#define PI 3.14159265359f

class Camera
{
public:
	Camera(double& time, int& width, int& height, bool* input, 
		float zoom = 50, glm::vec3 focus = glm::vec3(0, 0, 0), glm::vec3 direction = glm::vec3(0, 0, 1));
	
	glm::f32* getProjection();
	glm::mat4& getView();
	glm::vec3& getFocus();
	glm::vec3& getPosition();

	
	void rotateCamera(float x, float y);


	void adjust(GLFWwindow* window);
	void refresh();


	float zoom_;

private:
	void moveCamera();

private:
	double& time_;

	glm::vec3 focus_;
	glm::vec3 direction_;
	glm::vec3 position_;
	glm::vec3 up_;

	glm::f32* projectionPtr_;

	glm::mat4 projection_;
	glm::mat4 view_;

	float angleH_;
	float angleV_;

	float fov_;

	bool* input_;

	int& width_;
	int& height_;

	float speeds_[3];
	const float acceleration_;
	const float friction_;
};

