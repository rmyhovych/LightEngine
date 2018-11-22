#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"

class Window
{
public:
	GLFWwindow* window_;

	Window(int width = 1200, int height = 800);
	~Window();

	bool* getInput();

	void input();
	void mouseInput(Camera& camera);

private:
	bool* keyInput_;

	bool pressed_;
	glm::vec2 cursorPosition_;
	float inputForce_;

};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
