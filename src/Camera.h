#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <iostream>

#include <cmath>

#define PI 3.14159265359f

class Camera
{
public:
	Camera(int width, int height, float zoom = 5, 
		float angleH = PI / 2, float angleV = PI / 2,
		const glm::vec3& focus = glm::vec3(0, 0, 0));
	

	void resize(int width, int height);
	
	glm::mat4& getPV();
	
	void rotate(float x, float y);
	void move(float x, float y, float z);
	void zoom(float delta);
	void setZoom(float newZoom);

	void setDirection(const glm::vec3& direction);

	glm::vec3& getFocus();

	void setFocus(const glm::vec3& focus, const glm::vec3& up = { 0, 1, 0 });

private:
	void update();

private:

	float m_zoom;

	glm::vec3 m_focus;
	glm::vec3 m_direction;
	glm::vec3 m_position;
	glm::vec3 m_up;

	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 m_pv;


	float m_angleH;
	float m_angleV;
};
