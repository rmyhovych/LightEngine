#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"

class GLWindow
{
public:
	GLFWwindow* window_;

	static int width;
	static int height;


	GLWindow(int width = 1200, int height = 800);
	~GLWindow();

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
