#include "Window.h"

#include <stdexcept>

Window::Window(int width, int heigth) :
	m_width(width),
	m_height(heigth)
{
	gl3wInit();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, "PicoEngine", NULL, NULL);

	if (m_window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}
	
	glfwMakeContextCurrent(m_window);

	glViewport(0, 0, m_width, m_height);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::isOpen()
{
	return glfwWindowShouldClose(m_window) == 0;
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}