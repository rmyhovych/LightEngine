#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WindowGL
{
public:
	GLFWwindow* window_;

	WindowGL(int width = 800, int height = 800);

	bool* getInput();

	void input();

private:
	int width_;
	int height_;

	bool* keyInput_;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
