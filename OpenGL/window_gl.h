#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WindowGL
{
public:
	GLFWwindow* window_;

	WindowGL(int width = 1200, int height = 800);
	~WindowGL();

	bool* getInput();

	void input();

private:
	bool* keyInput_;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
