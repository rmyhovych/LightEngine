#pragma once

#include "gl.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window(
		int width = 800,
		int heigth = 600);

	~Window();

	bool isOpen();

	void swapBuffers();

private:
	int m_width;
	int m_height;

	GLFWwindow* m_window;
};
